# openETL

openETL is a C++ utility library distributed as headers under `include/etl`.
The umbrella header is `include/etl.hpp`; individual components can also be
included directly.

## Components

The headers cover utilities for benchmarking, enums, errors and exceptions,
files and I/O, functions, hashing, indexing, iterators and containers,
lexing and tokens, random values, sorting, streams, tests, types, and warnings.
See the header pages in this API reference for declarations and details.

## Generating the API reference

Install Doxygen, then run this command from the repository root:

```text
doxygen Doxyfile
```

The generated HTML reference is written to `output/doxygen/html`.
