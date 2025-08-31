# README

## "Style guide"

In case I forget, this directory is for scripts and scripts only; keep it casual.

Ideally, subdirectories are at most one level deep and should only serve to vaguely organize the scripts by category.

Remember, labels and categories only add restrictions and, in excess, prevent actual work from being done. Letting the scripts roam free allows us to piece them together without getting lost in semantics.

## Overview/plan

- **compile.js**: "Compiles" programs; in quotes because some programs (e.g. Python, JavaScript) don't need to be compiled, but the script should generate an executable anyway.
- **cached_compile.js**: Compiles programs, but caching executables to be reused in the future.
- **run.js**: Runs executables, keeping track of resource consumption. Remember to keep it simple; you've used OnlineGDB for a couple weeks now and its limited feature set never got in the way.
- **run_using_inputs.js**: Runs an executable with inputs from a directory. It's safe to say these runs are batched and should run in parallel.
- **expand_c_cpp_includes.js**: Expands C/C++ local (quoted) include directives using code in the `Competitive-Programming/include` directory.
- **cpt.js**: Command-line interface. This script and this script only should be the bridge between user and tool; no other script should have to worry about this.
