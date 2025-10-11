# Design Document

## Overview

The Limit Tooling Ecosystem is designed as a unified, extensible platform that transforms the existing Limit language implementation into a complete development environment. The ecosystem follows a modular architecture where each tool operates independently but shares common infrastructure, configuration, and data formats. The design leverages the existing Limit compiler infrastructure (scanner, parser, AST, VM) as the foundation for all tooling components.

The ecosystem is built around a central `limitly` command-line interface that provides access to all tools through subcommands, similar to how `cargo` works for Rust or `go` works for Go. This unified interface ensures consistency across all tools while maintaining the flexibility to use individual components independently.

## Architecture

### Core Architecture Principles

1. **Unified Interface**: Single entry point (`limitly`) with consistent subcommands
2. **Shared Infrastructure**: Reuse existing compiler components (scanner, parser, AST, VM)
3. **Modular Design**: Each tool is a separate module that can be used independently
4. **Configuration-Driven**: Single project configuration file drives all tool behavior
5. **Extensible Framework**: Plugin architecture for adding new tools and features

### System Components

```
┌─────────────────────────────────────────────────────────────┐
│                    Limitly CLI Interface                    │
├─────────────────────────────────────────────────────────────┤
│  init │ build │ test │ lint │ format │ debug │ doc │ profile │
├─────────────────────────────────────────────────────────────┤
│                   Tool Orchestrator                         │
├─────────────────────────────────────────────────────────────┤
│           Configuration Manager │ Project Context           │
├─────────────────────────────────────────────────────────────┤
│  Package  │  Build   │  Test    │  Lint    │  Format       │
│  Manager  │  System  │  Runner  │  Engine  │  Engine       │
├─────────────────────────────────────────────────────────────┤
│  Debug    │  Doc     │  LSP     │  Profile │  CI/CD        │
│  Server   │  Gen     │  Server  │  Engine  │  Integration  │
├─────────────────────────────────────────────────────────────┤
│              Shared Compiler Infrastructure                 │
│        Scanner │ Parser │ AST │ Type Checker │ VM           │
├─────────────────────────────────────────────────────────────┤
│                    File System Layer                        │
│         Project Files │ Cache │ Dependencies │ Artifacts    │
└─────────────────────────────────────────────────────────────┘
```

### Configuration System

The ecosystem uses a single `limit.toml` configuration file that defines all project settings:

```toml
[project]
name = "my-limit-project"
version = "1.0.0"
authors = ["Developer Name <dev@example.com>"]
description = "A Limit project"
license = "MIT"

[build]
target = "executable"  # or "library"
optimization = "release"  # or "debug"
output_dir = "bin"

[dependencies]
# External dependencies
http_client = "1.2.0"
json_parser = "2.1.0"

[dev-dependencies]
# Development-only dependencies
test_framework = "1.0.0"

[test]
parallel = true
coverage_threshold = 80
timeout = 30

[lint]
max_line_length = 100
enforce_naming_conventions = true
allow_unused_variables = false

[format]
indent_size = 4
use_tabs = false
max_line_length = 100

[doc]
output_format = "html"
include_private = false
theme = "default"
```

## Components and Interfaces

### 1. CLI Interface and Tool Orchestrator

**Purpose**: Provides unified command-line interface and coordinates tool execution.

**Key Classes**:
- `CliInterface`: Main entry point, argument parsing, help system
- `ToolOrchestrator`: Manages tool lifecycle, configuration loading, error handling
- `CommandRegistry`: Registry of available tools and their metadata

**Interfaces**:
```cpp
class Tool {
public:
    virtual ~Tool() = default;
    virtual std::string getName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual int execute(const ToolContext& context) = 0;
    virtual void printHelp() const = 0;
};

class ToolContext {
public:
    const ProjectConfig& getConfig() const;
    const std::vector<std::string>& getArguments() const;
    const std::filesystem::path& getProjectRoot() const;
    Logger& getLogger() const;
};
```

### 2. Configuration Manager

**Purpose**: Manages project configuration, validation, and tool-specific settings.

**Key Classes**:
- `ProjectConfig`: Main configuration container
- `ConfigValidator`: Validates configuration consistency
- `ConfigMigrator`: Handles configuration format updates

**Configuration Loading Strategy**:
1. Load `limit.toml` from project root
2. Merge with user-level configuration (`~/.limit/config.toml`)
3. Apply command-line overrides
4. Validate configuration consistency
5. Provide tool-specific configuration views

### 3. Package Manager

**Purpose**: Handles dependency resolution, installation, and management.

**Key Classes**:
- `PackageManager`: Main package management interface
- `DependencyResolver`: Resolves version conflicts and transitive dependencies
- `PackageRegistry`: Interface to package repositories
- `LockFileManager`: Manages `limit.lock` for reproducible builds

**Package Resolution Algorithm**:
1. Parse dependencies from `limit.toml`
2. Fetch package metadata from registries
3. Resolve version constraints using semantic versioning
4. Download and cache packages locally
5. Generate lock file with exact versions
6. Validate package integrity and signatures

### 4. Build System

**Purpose**: Compiles Limit source code with optimization and caching.

**Key Classes**:
- `BuildEngine`: Main build orchestration
- `CompilationUnit`: Represents a single compilation target
- `BuildCache`: Manages incremental compilation cache
- `TargetManager`: Handles cross-platform compilation

**Build Process**:
1. Analyze source files and dependencies
2. Check build cache for up-to-date artifacts
3. Generate compilation plan with dependency ordering
4. Execute compilation units in parallel where possible
5. Link final executable or library
6. Update build cache with new artifacts

### 5. Test Framework and Runner

**Purpose**: Provides comprehensive testing capabilities with coverage analysis.

**Key Classes**:
- `TestRunner`: Main test execution engine
- `TestDiscovery`: Finds and categorizes test files
- `CoverageAnalyzer`: Tracks code coverage during test execution
- `TestReporter`: Generates test results in various formats

**Test Execution Strategy**:
1. Discover test files using naming conventions (`*_test.lm`, `test_*.lm`)
2. Parse test files to extract test functions and metadata
3. Execute tests in parallel with isolated environments
4. Collect coverage data using VM instrumentation
5. Generate reports in multiple formats (console, JUnit XML, HTML)

### 6. Linting and Formatting Engine

**Purpose**: Enforces code style and detects potential issues.

**Key Classes**:
- `LintEngine`: Main linting orchestration
- `RuleRegistry`: Registry of available linting rules
- `FormatEngine`: Code formatting with configurable rules
- `StyleChecker`: Validates code against style guidelines

**Linting Rules Architecture**:
```cpp
class LintRule {
public:
    virtual ~LintRule() = default;
    virtual std::string getRuleName() const = 0;
    virtual std::string getDescription() const = 0;
    virtual std::vector<LintIssue> check(const AST::Node& node) const = 0;
};

class LintIssue {
public:
    enum Severity { Error, Warning, Info };
    
    Severity severity;
    std::string message;
    SourceLocation location;
    std::string suggestion;
};
```

### 7. Debug Server

**Purpose**: Provides debugging capabilities with IDE integration support.

**Key Classes**:
- `DebugServer`: DAP (Debug Adapter Protocol) server implementation
- `BreakpointManager`: Manages breakpoints and watchpoints
- `DebugSession`: Represents an active debugging session
- `VariableInspector`: Provides variable inspection and evaluation

**Debug Protocol Support**:
- Implements Debug Adapter Protocol (DAP) for IDE integration
- Supports standard debugging operations (step, continue, pause)
- Provides variable inspection and expression evaluation
- Integrates with existing VM for execution control

### 8. Documentation Generator

**Purpose**: Generates comprehensive API documentation from source code.

**Key Classes**:
- `DocGenerator`: Main documentation generation engine
- `CommentParser`: Extracts and parses documentation comments
- `TemplateEngine`: Renders documentation using customizable templates
- `CrossReferencer`: Builds symbol cross-references and navigation

**Documentation Extraction**:
1. Parse source files to extract AST with comments
2. Identify public APIs (functions, classes, modules)
3. Extract documentation comments using standard format
4. Build symbol cross-reference database
5. Generate output using configurable templates
6. Create navigation structure and search index

### 9. Language Server Protocol (LSP) Implementation

**Purpose**: Provides IDE integration with intelligent code assistance.

**Key Classes**:
- `LanguageServer`: Main LSP server implementation
- `CompletionProvider`: Provides intelligent autocomplete suggestions
- `DiagnosticsEngine`: Real-time error checking and reporting
- `SymbolIndex`: Maintains project-wide symbol database

**LSP Features**:
- Autocomplete with context-aware suggestions
- Go-to-definition and find-references
- Real-time diagnostics with error squiggles
- Hover information with type and documentation
- Symbol search and workspace navigation
- Refactoring support (rename, extract function)

### 10. Performance Profiler

**Purpose**: Analyzes application performance and identifies bottlenecks.

**Key Classes**:
- `ProfileEngine`: Main profiling orchestration
- `SamplingProfiler`: Statistical sampling profiler
- `MemoryTracker`: Tracks memory allocations and usage
- `ReportGenerator`: Generates performance reports and visualizations

**Profiling Strategy**:
1. Instrument VM with profiling hooks
2. Collect samples during program execution
3. Track function call times and memory allocations
4. Generate flame graphs and call trees
5. Identify hotspots and optimization opportunities
6. Provide actionable performance recommendations

## Data Models

### Project Structure

```
my-limit-project/
├── limit.toml              # Project configuration
├── limit.lock              # Dependency lock file
├── src/                    # Source code
│   ├── main.lm
│   └── lib/
├── tests/                  # Test files
│   ├── unit/
│   └── integration/
├── docs/                   # Documentation
├── .limit/                 # Tool cache and metadata
│   ├── cache/
│   ├── deps/
│   └── build/
└── target/                 # Build artifacts
    ├── debug/
    └── release/
```

### Dependency Model

```cpp
struct Dependency {
    std::string name;
    std::string version_constraint;
    std::string registry_url;
    bool is_dev_dependency;
    std::vector<std::string> features;
};

struct ResolvedDependency {
    std::string name;
    std::string exact_version;
    std::string source_url;
    std::string checksum;
    std::vector<ResolvedDependency> transitive_deps;
};
```

### Build Artifact Model

```cpp
struct BuildArtifact {
    std::string name;
    ArtifactType type;  // Executable, Library, Object
    std::filesystem::path path;
    std::chrono::system_clock::time_point timestamp;
    std::vector<std::string> source_files;
    std::string checksum;
};
```

## Error Handling

### Error Categories

1. **Configuration Errors**: Invalid or missing configuration
2. **Dependency Errors**: Package resolution or download failures
3. **Build Errors**: Compilation or linking failures
4. **Test Errors**: Test execution or assertion failures
5. **Runtime Errors**: Tool execution or system errors

### Error Reporting Strategy

```cpp
class ToolError {
public:
    enum Category { Configuration, Dependency, Build, Test, Runtime };
    
    Category category;
    std::string message;
    std::optional<SourceLocation> location;
    std::vector<std::string> suggestions;
    std::optional<std::string> help_url;
};
```

### Error Recovery

- Graceful degradation when non-critical tools fail
- Detailed error messages with actionable suggestions
- Integration with existing Limit error reporting system
- Structured error output for IDE integration

## Testing Strategy

### Unit Testing

- Test individual tool components in isolation
- Mock external dependencies (file system, network)
- Comprehensive test coverage for core functionality
- Property-based testing for complex algorithms

### Integration Testing

- End-to-end testing of complete tool workflows
- Test tool interactions and data flow
- Validate configuration loading and validation
- Test error handling and recovery scenarios

### Performance Testing

- Benchmark critical operations (build, test execution)
- Memory usage analysis for large projects
- Scalability testing with varying project sizes
- Regression testing for performance improvements

### Test Infrastructure

```cpp
class ToolTestFixture {
public:
    void setupTempProject(const ProjectConfig& config);
    void addSourceFile(const std::string& path, const std::string& content);
    void addTestFile(const std::string& path, const std::string& content);
    ToolResult runTool(const std::string& tool_name, const std::vector<std::string>& args);
    void verifyOutput(const std::string& expected);
    void verifyFileExists(const std::string& path);
};
```

## Implementation Phases

### Phase 1: Core Infrastructure
- CLI interface and tool orchestrator
- Configuration management system
- Project initialization and detection
- Basic build system integration

### Phase 2: Essential Tools
- Package manager with dependency resolution
- Enhanced build system with caching
- Test framework and runner
- Basic linting and formatting

### Phase 3: Advanced Features
- Debug server with DAP support
- Documentation generator
- Language server implementation
- Performance profiler

### Phase 4: Ecosystem Integration
- CI/CD integration templates
- IDE plugins and extensions
- Package registry infrastructure
- Advanced tooling features

This design provides a solid foundation for building a comprehensive tooling ecosystem that leverages the existing Limit language infrastructure while providing a modern, unified development experience.