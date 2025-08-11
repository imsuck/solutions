#!/usr/bin/env python3
"""
expand_includes.py

Recursively expand C/C++ #include "file" directives (only quoted includes).
Respects `#pragma once` and optionally produces output in g++ -E style with `#line <lineno> "<filename>"` pragmas.
Also checks for cyclic dependencies before expansion.
Yes, this is ChatGPT-generated.
"""

from __future__ import annotations
import argparse
import logging
import os
import re
import sys
from typing import List, Set, Optional, Dict

INCLUDE_RE = re.compile(r'^(?P<prefix>\s*#\s*include\s*)"(?P<path>[^"]+)"(?P<suffix>.*)$')
PRAGMA_ONCE_RE = re.compile(r'^\s*#\s*pragma\s+once\b')

def resolve_include(include_path: str, cur_dir: str, include_dirs: List[str]) -> Optional[str]:
    candidates = [os.path.join(cur_dir, include_path)]
    candidates += [os.path.join(d, include_path) for d in include_dirs]
    for c in candidates:
        if os.path.isfile(c):
            return os.path.realpath(c)
    return None

def read_text(path: str) -> str:
    with open(path, 'r', encoding='utf-8', errors='surrogateescape') as f:
        return f.read()

def has_pragma_once(text: str) -> bool:
    for line in text.splitlines():
        if PRAGMA_ONCE_RE.match(line):
            return True
    return False

def build_dependency_graph(path: str, include_dirs: List[str], graph: Dict[str, Set[str]]) -> None:
    real_path = os.path.realpath(path)
    if real_path in graph:
        return
    graph[real_path] = set()
    cur_dir = os.path.dirname(real_path) or '.'
    try:
        lines = read_text(real_path).splitlines()
    except Exception:
        return
    for line in lines:
        m = INCLUDE_RE.match(line)
        if m:
            inc_path = m.group('path')
            resolved = resolve_include(inc_path, cur_dir, include_dirs)
            if resolved:
                graph[real_path].add(resolved)
                build_dependency_graph(resolved, include_dirs, graph)

def topo_sort_check(graph: Dict[str, Set[str]]) -> None:
    visited: Dict[str, int] = {}
    def dfs(node: str):
        if visited.get(node, 0) == 1:
            raise RuntimeError(f"Cyclic dependency detected at {node}")
        if visited.get(node, 0) == 2:
            return
        visited[node] = 1
        for neigh in graph[node]:
            dfs(neigh)
        visited[node] = 2
    for node in graph:
        if visited.get(node, 0) == 0:
            dfs(node)

def expand_file(path: str,
                include_dirs: List[str],
                included_once: Set[str],
                logger: logging.Logger,
                line_pragmas: bool,
                depth: int = 0,
                max_depth: Optional[int] = None,
                error_on_missing: bool = False) -> str:
    if max_depth is not None and depth > max_depth:
        logger.warning("Max depth %s reached while expanding %s", max_depth, path)
        return ''

    real_path = os.path.realpath(path)
    try:
        text = read_text(real_path)
    except Exception as e:
        logger.error("Failed to read %s: %s", path, e)
        if error_on_missing:
            raise
        return ''

    pragma_once = has_pragma_once(text)
    if pragma_once and real_path in included_once:
        logger.info("Skipping due to #pragma once: %s", real_path)
        return ''

    if pragma_once:
        included_once.add(real_path)

    logger.info("Expanding: %s", real_path)

    out_lines: List[str] = []
    cur_dir = os.path.dirname(real_path) or '.'

    if line_pragmas:
        # Entering file: g++ uses # 1 "filename"
        out_lines.append(f'#line 1 "{real_path}"\n')

    lines = text.splitlines(keepends=True)
    for i, line in enumerate(lines, start=1):
        m = INCLUDE_RE.match(line)
        if not m:
            out_lines.append(line)
            continue

        inc_path = m.group('path')
        logger.debug('Found include "%s" in %s:%d', inc_path, path, i)
        resolved = resolve_include(inc_path, cur_dir, include_dirs)
        if not resolved:
            msg = f"Could not resolve include \"{inc_path}\" from {path}:{i}"
            if error_on_missing:
                logger.error(msg)
                raise FileNotFoundError(msg)
            else:
                logger.warning(msg)
                out_lines.append(line)
                continue

        expanded = expand_file(resolved, include_dirs, included_once, logger,
                               line_pragmas=line_pragmas,
                               depth=depth+1, max_depth=max_depth,
                               error_on_missing=error_on_missing)
        expanded = ''.join(
            line for line in expanded.splitlines(keepends=True)
            if not PRAGMA_ONCE_RE.match(line)
        )
        out_lines.append(expanded)

        if line_pragmas:
            # After include, restore line numbering in current file
            out_lines.append(f'#line {i+1} "{real_path}"\n')

    return ''.join(out_lines)

def build_arg_parser() -> argparse.ArgumentParser:
    p = argparse.ArgumentParser(description='Recursively expand C/C++ #include "file" directives, optionally g++ -E style')
    p.add_argument('input', help='Input source file to expand')
    p.add_argument('-I', '--include-dir', action='append', default=[], help='Additional include directory to search')
    p.add_argument('-o', '--output', default=None, help='Write expanded output to this file')
    p.add_argument('-v', '--verbose', action='store_true', help='Enable verbose logging')
    p.add_argument('--max-depth', type=int, default=None, help='Maximum recursion depth')
    p.add_argument('--error-on-missing', action='store_true', help='Exit with error if an included file cannot be found')
    p.add_argument('--line-pragmas', action='store_true', help='Emit g++-style #line lineno "filename" pragmas')
    return p

def configure_logger(verbose: bool) -> logging.Logger:
    logger = logging.getLogger('expand_includes')
    handler = logging.StreamHandler()
    handler.setFormatter(logging.Formatter('%(levelname)s: %(message)s'))
    logger.addHandler(handler)
    logger.propagate = False
    logger.setLevel(logging.DEBUG if verbose else logging.INFO)
    return logger

def main(argv: Optional[List[str]] = None) -> int:
    argv = argv if argv is not None else sys.argv[1:]
    parser = build_arg_parser()
    args = parser.parse_args(argv)

    logger = configure_logger(args.verbose)

    input_path = args.input
    if not os.path.isfile(input_path):
        logger.error('Input file not found: %s', input_path)
        return 2

    include_dirs = [os.path.realpath(d) for d in args.include_dir]

    graph: Dict[str, Set[str]] = {}
    build_dependency_graph(input_path, include_dirs, graph)
    try:
        topo_sort_check(graph)
    except RuntimeError as e:
        logger.error(str(e))
        return 1

    try:
        expanded = expand_file(input_path, include_dirs, set(), logger,
                               line_pragmas=args.line_pragmas,
                               depth=0, max_depth=args.max_depth,
                               error_on_missing=args.error_on_missing)
    except Exception as e:
        logger.exception('Failed to expand includes: %s', e)
        return 1

    if args.output:
        try:
            with open(args.output, 'w', encoding='utf-8', errors='surrogateescape') as f:
                f.write(expanded)
        except Exception as e:
            logger.exception('Failed to write output: %s', e)
            return 1
    else:
        sys.stdout.write(expanded)

    return 0

if __name__ == '__main__':
    raise SystemExit(main())
