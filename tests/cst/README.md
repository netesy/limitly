# CST Parser Test Suite

This directory contains comprehensive tests for the Concrete Syntax Tree (CST) parser architecture.

## Test Structure

- `scanner/` - Tests for enhanced scanner with trivia preservation
- `parser/` - Tests for CST parser with error recovery
- `ast_builder/` - Tests for CST to AST transformation
- `integration/` - End-to-end integration tests and performance benchmarks

## Running Tests

```bash
# Run all CST tests
./tests/cst/run_cst_tests.bat

# Run specific test category
./bin/limitly.exe tests/cst/scanner/whitespace_preservation.lm
./bin/limitly.exe tests/cst/parser/valid_syntax.lm
./bin/limitly.exe tests/cst/ast_builder/transformation.lm
./bin/limitly.exe tests/cst/integration/round_trip.lm
```

## Test Categories

### Scanner Tests
- Whitespace preservation
- Comment preservation  
- Error token generation
- Trivia attachment

### Parser Tests
- Valid syntax parsing
- Invalid syntax recovery
- Error node creation
- Partial node construction

### AST Builder Tests
- Transformation accuracy
- Error-tolerant conversion
- Source mapping preservation

### Integration Tests
- Round-trip source reconstruction
- Performance benchmarks
- Error recovery validation