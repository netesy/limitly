# **Limitly Frame Spec — Modern OOP (Traits + Composition)**

## **Overview**

`frame` is the primary **object-oriented construct** in Limitly, following modern principles:

* ✅ **Composition over inheritance** (no class hierarchies)
* ✅ **Trait-based polymorphism** (interfaces)
* ✅ **Encapsulation** with visibility modifiers
* ✅ **Concurrency integration** (parallel/concurrent)
* ✅ **Lifecycle management** (init/deinit)
* ✅ **Sequential by default** (opt-in concurrency)

> **Philosophy**: Frames are Rust-style structs + Go-style interfaces + built-in concurrency.

---

## **1. Frame Declaration**

```limit
frame <FrameName> {
    // Fields (default: private if no modifier)
    var <field>: <type>           // private (default)
    prot var <field>: <type>      // protected (trait access)
    pub var <field>: <type>       // public

    // Methods (default: private if no modifier)
    fn <method>(<args>) { ... }         // private (default)
    prot fn <method>(<args>) { ... }    // protected
    pub fn <method>(<args>) { ... }     // public

    // Lifecycle hooks (typically public)
    pub init(<args>) { ... }
    pub deinit() { ... }

    // Optional parallel block (direct SharedCell operations)
    parallel(<options>) {
        iter(<iterator>) {
            // Direct code - SharedCell access
        }
    }

    // Optional concurrent block - batch mode (task-based)
    concurrent(<options>, mode=batch) {
        task(<iterator>) {
            // Bounded concurrent tasks
        }
    }

    // Optional concurrent block - stream mode (worker-based)
    concurrent(<options>, mode=stream) {
        worker(<event>) {
            // Unbounded event processing
        }
    }
}
```

**Key Points**:
- **Default visibility is private** - no need to write `private` keyword
- **No inheritance** - frames cannot extend other frames
- **Implements traits** for polymorphism
- **Embeds other frames** for composition
- **Sequential by default** unless concurrency blocks defined

---

## **2. Visibility Rules**

| Modifier              | Access Scope                                    | When to Use |
| --------------------- | ----------------------------------------------- | ----------- |
| (none — default)      | Only within the declaring frame                 | Internal implementation |
| `prot` (protected)    | Within frame + accessible via trait methods     | Trait-accessible state |
| `pub` (public)        | Accessible from anywhere                        | Public API |

**Examples**:

```limit
frame Service {
    var secret_key: string = "hidden"     // private (default)
    prot var config: Config               // protected
    pub var status: string = "active"     // public
    
    fn internal_check() { ... }           // private method (default)
    prot fn validate_config() { ... }     // protected method
    pub fn get_status(): string { ... }   // public method
}
```

**Enforcement**:
- Compile-time checks for field/method access
- All concurrency blocks can access `pub` and `prot` fields only
- Trait methods can access `prot` and `pub` fields only

---

## **3. Concurrency Models**

### **Parallel Block — Direct SharedCell Access (CPU-Bound)**

```limit
parallel(
    cores = Auto | Int,       // CPU cores (default: Auto)
    timeout = Duration?,      // max execution time
    grace = Duration?,        // graceful shutdown
    on_error = Stop | Continue | Partial
) {
    // Direct code only - NO "task" or "worker" keyword
    iter(i in 0..999) {
        results[i] = compute(data[i])  // SharedCell operations
    }
}
```

**Characteristics**:
- ✅ Fork-join parallelism (CPU-bound)
- ✅ Direct code execution with `iter()`
- ✅ SharedCell for atomic access
- ✅ Synchronous parallel execution
- ✅ No channels required

---

### **Concurrent Block — Batch Mode (Bounded Tasks)**

```limit
concurrent(
    ch = ch,      // output channel (required)
    mode = batch,             // batch processing mode
    cores = Auto | Int,       // worker threads (default: Auto)
    timeout = Duration?,      // max execution time (default: 20s)
    grace = Duration?,        // graceful shutdown (default: 500ms)
    on_error = Stop | Continue | Retry,
    on_timeout = Partial | Stop
) {
    task(i in range) {
        // Bounded concurrent tasks with channel output
        var result = process(i)
        ch.send(result)
    }
}
```

**Characteristics**:
- ✅ Bounded concurrency (fixed iteration range)
- ✅ Task-based syntax: `task(i in range)`
- ✅ Channel-based output
- ✅ Atomic operations on shared state
- ✅ Auto-closes channel when complete
- ✅ Good for parallelizing bounded work over I/O

**Example**:

```limit
frame BatchProcessor : Processor {
    pub var shared_counter: int = 0
    pub var results: array[int] = []
    
    concurrent(ch=result_channel, mode=batch, cores=4, 
               timeout=20s, on_error=Stop) {
        task(i in 1..100) {
            var computed = heavy_io_operation(i)  // I/O bound
            self.shared_counter += 1  // atomic increment
            result_channel.send(computed)
        }
    }  // result_channel auto-closes
    
    pub fn process(): array[int] {
        self.concurrent.run()
        
        // Collect results from channel
        iter(result in result_channel) {
            results.push(result)
        }
        
        return results
    }
}
```

---

### **Concurrent Block — Stream Mode (Unbounded Workers)**

```limit
concurrent(
    events: <EventType>,      // event source/stream
    ch = ch,      // output channel (required)
    mode = stream,            // stream processing mode
    cores = Auto | Int,       // worker threads (default: Auto)
    timeout = Duration?,      // max execution time (default: 15s)
    grace = Duration?,        // graceful shutdown (default: 500ms)
    on_error = Stop | Continue | Retry,
    on_timeout = Partial | Stop
) {
    worker(event) {
        // Process incoming events indefinitely
        var result = handle(event)
        ch.send(result)
    }
}
```

**Characteristics**:
- ✅ Unbounded concurrency (event stream)
- ✅ Worker-based syntax: `worker(event)`
- ✅ Channel-based input/output
- ✅ Event-driven processing
- ✅ Runs until stream exhausted or timeout
- ✅ Good for continuous I/O streams

**Example**:

```limit
frame StreamProcessor : EventHandler {
    pub var events_processed: int = 0
    var event_stream: Stream  // private by default
    
    pub init(stream: Stream) {
        event_stream = stream
    }
    
    concurrent(events: event_stream, ch=output_channel, 
               mode=stream, cores=8, timeout=60s, on_error=Continue) {
        worker(event) {
            // Process each incoming event
            var processed = handle_event(event)
            self.events_processed += 1  // atomic
            output_channel.send(processed)
        }
    }  // output_channel auto-closes
    
    pub fn run() {
        self.concurrent.start()
        
        // Consume output stream
        iter(result in output_channel) {
            log_result(result)
        }
    }
}
```

---

## **4. Trait System**

### **Trait Definition**

```limit
trait <TraitName> {
    fn <method_signature>(<args>): <return_type>
    fn <method_with_default>(<args>) { 
        // default implementation
    }
}
```

### **Trait Implementation**

```limit
frame MyFrame : TraitA, TraitB {
    // Must implement all required trait methods
    pub fn required_method() { ... }
}
```

**Example**:

```limit
trait Processor {
    fn process(data: array[int]): array[int]
    fn validate(): bool
}

trait Logger {
    fn log(msg: string)
    fn log_error(msg: string) {
        // default implementation
        self.log("ERROR: " + msg)
    }
}

frame DataProcessor : Processor, Logger {
    pub var results: array[int] = []
    var log_file: File  // private by default
    
    pub init(path: string) {
        log_file = open(path)
    }
    
    // Implement Processor trait
    pub fn process(data: array[int]): array[int] {
        for val in data {
            results.push(compute(val))
        }
        return results
    }
    
    pub fn validate(): bool {
        return results.len > 0
    }
    
    // Implement Logger trait
    pub fn log(msg: string) {
        log_file.write(msg + "\n")
    }
    
    pub deinit() {
        log_file.close()
    }
}
```

---

## **5. Composition**

```limit
frame Engine {
    pub var rpm: int = 0
    pub fn start() { rpm = 1000 }
    pub deinit() { print("Engine stopped") }
}

frame Transmission {
    pub var gear: int = 1
    pub fn shift_up() { gear += 1 }
}

frame Car {
    // Composition: embed frames directly
    pub var engine: Engine = Engine()
    pub var transmission: Transmission = Transmission()
    pub var speed: int = 0
    
    pub fn drive() {
        engine.start()           // delegate to composed frame
        transmission.shift_up()
        speed = engine.rpm / 100
    }
    
    pub deinit() {
        print("Car destroyed")
        // engine.deinit() and transmission.deinit() called automatically
    }
}
```

**Composition Rules**:
- ✅ Frames can embed other frames as fields
- ✅ Embedded frames auto-destroyed when parent destroyed
- ✅ Destruction order: children first, then parent
- ✅ Cross-mode composition allowed (sequential ↔ parallel ↔ concurrent)

---

## **6. Complete Concurrency Examples**

### **Parallel: Matrix Multiplication**

```limit
frame MatrixMultiplier {
    pub var result: array[array[float]] = []
    var matrix_a: array[array[float]]  // private
    var matrix_b: array[array[float]]  // private
    
    pub init(a: array[array[float]], b: array[array[float]]) {
        matrix_a = a
        matrix_b = b
        result = allocate_matrix(a.len, b[0].len)
    }
    
    parallel(cores=8, timeout=30s) {
        iter(i in 0..matrix_a.len-1) {
            iter(j in 0..matrix_b[0].len-1) {
                var sum: float = 0.0
                iter(k in 0..matrix_a[0].len-1) {
                    sum += self.matrix_a[i][k] * self.matrix_b[k][j]
                }
                self.result[i][j] = sum  // SharedCell atomic write
            }
        }
    }
    
    pub fn multiply(): array[array[float]] {
        self.parallel.run()
        return result
    }
}
```

---

### **Concurrent (Batch): Database Batch Queries**

```limit
trait DatabaseProcessor {
    fn process_batch(ids: array[int]): array[Result]
}

frame BatchQueryProcessor : DatabaseProcessor {
    var db: Database  // private
    pub var results: array[Result] = []
    pub var processed_count: int = 0
    
    pub init(db_conn: Database) {
        db = db_conn
    }
    
    concurrent(ch=result_channel, mode=batch, cores=10,
               timeout=30s, on_error=Continue) {
        task(id in user_ids) {
            // Each task performs I/O-bound database query
            var user = self.db.query("SELECT * FROM users WHERE id = ?", id)
            self.processed_count += 1  // atomic increment
            result_channel.send(user)
        }
    }  // result_channel auto-closes
    
    pub fn process_batch(ids: array[int]): array[Result] {
        user_ids = ids
        self.concurrent.run()
        
        // Collect all results
        iter(user in result_channel) {
            results.push(user)
        }
        
        return results
    }
    
    pub deinit() {
        db.close()
    }
}
```

---

### **Concurrent (Stream): WebSocket Handler**

```limit
trait WebSocketHandler {
    fn handle_connections()
}

frame RealtimeServer : WebSocketHandler {
    pub var connections_handled: int = 0
    pub var messages_sent: int = 0
    var websocket_stream: Stream  // private
    
    pub init(ws: Stream) {
        websocket_stream = ws
    }
    
    concurrent(events: websocket_stream, ch=response_channel,
               mode=stream, cores=16, timeout=3600s, on_error=Continue) {
        worker(message) {
            // Process each incoming WebSocket message
            var response = self.process_message(message)
            self.connections_handled += 1  // atomic
            response_channel.send(response)
        }
    }  // response_channel auto-closes
    
    fn process_message(msg: Message): Response {  // private method
        self.messages_sent += 1
        return Response { data: "Echo: " + msg.data }
    }
    
    pub fn handle_connections() {
        self.concurrent.start()
        
        // Send responses back to clients
        iter(response in response_channel) {
            broadcast(response)
        }
    }
    
    pub deinit() {
        print("Handled " + connections_handled + " connections")
    }
}
```

---

### **Mixed Concurrency: Complete Pipeline**

```limit
trait DataPipeline {
    fn run(input: array[int])
}

// Step 1: Parallel CPU-intensive preprocessing
frame Preprocessor : Processor {
    pub var processed: array[int] = []
    var input: array[int]  // private
    
    parallel(cores=8) {
        iter(i in 0..input.len-1) {
            // Heavy CPU computation
            self.processed[i] = normalize(self.input[i])
        }
    }
    
    pub fn process(data: array[int]): array[int] {
        input = data
        processed = array[int](data.len)
        self.parallel.run()
        return processed
    }
}

// Step 2: Concurrent batch I/O operations
frame DatabaseWriter : DataSink {
    var db: Database  // private
    pub var written_count: int = 0
    
    pub init(database: Database) {
        db = database
    }
    
    concurrent(ch=write_channel, mode=batch, cores=10) {
        task(record in records) {
            // I/O-bound database writes
            self.db.insert(record)
            self.written_count += 1
            write_channel.send(record.id)
        }
    }
    
    pub fn write(data: array[int]) {
        records = data
        self.concurrent.run()
        
        iter(id in write_channel) {
            log("Wrote record: " + id)
        }
    }
}

// Step 3: Concurrent stream event logging
frame EventLogger : Logger {
    var log_file: File  // private
    var log_stream: Stream  // private
    
    pub init(path: string) {
        log_file = open(path)
        log_stream = create_stream()
    }
    
    concurrent(events: log_stream, ch=log_channel, mode=stream, cores=2) {
        worker(event) {
            self.log_file.write(event.message + "\n")
            log_channel.send(event.id)
        }
    }
    
    pub fn log(msg: string) {
        log_stream.send(LogEvent { message: msg })
    }
    
    pub deinit() {
        log_file.close()
    }
}

// Composition: Complete pipeline
frame CompleteDataPipeline : DataPipeline {
    pub var preprocessor: Preprocessor = Preprocessor()
    pub var writer: DatabaseWriter
    pub var logger: EventLogger
    
    pub init(db: Database, log_path: string) {
        writer = DatabaseWriter(db)
        logger = EventLogger(log_path)
    }
    
    pub fn run(input: array[int]) {
        logger.log("Starting pipeline...")
        
        // Step 1: Parallel CPU work
        var processed = preprocessor.process(input)
        logger.log("Preprocessing complete: " + processed.len + " items")
        
        // Step 2: Concurrent batch I/O
        writer.write(processed)
        logger.log("Database writes complete: " + writer.written_count)
        
        logger.log("Pipeline complete")
    }
    
    pub deinit() {
        // All child frames auto-destroyed
        print("Pipeline shutdown complete")
    }
}
```

---

## **7. Lifecycle Management**

### **Constructor (init)**

```limit
frame Database : Connectable {
    var connection: Connection  // private
    pub var is_connected: bool = false
    
    pub init(host: string, port: int) {
        connection = connect(host, port)
        is_connected = true
        print("Connected to " + host)
    }
}
```

### **Destructor (deinit)**

```limit
frame ResourcePool {
    var resources: array[Resource] = []  // private
    
    pub init(count: int) {
        iter(i in 0..count-1) {
            resources.push(allocate_resource())
        }
    }
    
    pub deinit() {
        for res in resources {
            res.cleanup()
        }
        print("All resources released")
    }
}
```

**Guarantees**:
- `init` called automatically on creation
- `deinit` called automatically on destruction
- `deinit` **guaranteed to run**, even if concurrency blocks panic
- Cascades to composed frames (children first)
- Channels auto-closed when concurrent blocks complete

---

## **8. Trait Objects & Polymorphism**

### **Static Dispatch (Compile-Time)**

```limit
fn process_data<T: Processor>(proc: T, data: array[int]) {
    var result = proc.process(data)  // static dispatch, no vtable
}
```

### **Dynamic Dispatch (Runtime)**

```limit
trait Processor {
    fn process(data: array[int]): array[int]
}

frame ParallelProcessor : Processor {
    pub var results: array[int] = []
    var data: array[int]  // private
    
    parallel(cores=4) {
        iter(i in 0..data.len-1) {
            self.results[i] = compute(self.data[i])
        }
    }
    
    pub fn process(input: array[int]): array[int] {
        data = input
        results = array[int](input.len)
        self.parallel.run()
        return results
    }
}

frame ConcurrentProcessor : Processor {
    pub var results: array[int] = []
    var data: array[int]  // private
    
    concurrent(ch=result_ch, mode=batch, cores=4) {
        task(i in 0..data.len-1) {
            var res = compute(self.data[i])
            result_ch.send(res)
        }
    }
    
    pub fn process(input: array[int]): array[int] {
        data = input
        self.concurrent.run()
        
        iter(res in result_ch) {
            results.push(res)
        }
        return results
    }
}

// Trait object - runtime polymorphism
fn run_processor(proc: &Processor, data: array[int]) {
    var result = proc.process(data)  // dynamic dispatch via vtable
}

var processors: array[&Processor] = [
    &ParallelProcessor(),
    &ConcurrentProcessor()
]
```

---

## **9. Worker/Task/Iter Access Rules**

| Context                   | Can Access         | Cannot Access | Syntax |
| ------------------------- | ------------------ | ------------- | ------ |
| `parallel` block          | `pub`, `prot` vars | (default) private | `iter()` |
| `concurrent` (batch)      | `pub`, `prot` vars | (default) private | `task()` |
| `concurrent` (stream)     | `pub`, `prot` vars | (default) private | `worker()` |

**Example**:

```limit
frame SecureProcessor : Processor {
    var encryption_key: string = "secret"  // private (cannot access)
    prot var temp_buffer: array[int] = []  // protected (can access)
    pub var results: array[int] = []       // public (can access)
    
    parallel(cores=4) {
        iter(i in 0..99) {
            // self.encryption_key  // ❌ compile error: private
            self.temp_buffer[i] = compute(i)  // ✅ OK: protected
            self.results[i] = self.temp_buffer[i] * 2  // ✅ OK: public
        }
    }
    
    concurrent(ch=out_ch, mode=batch, cores=4) {
        task(i in 0..99) {
            // self.encryption_key  // ❌ compile error: private
            self.temp_buffer[i] = process(i)  // ✅ OK: protected
            out_ch.send(self.results[i])  // ✅ OK: public
        }
    }
}
```

---

## **10. Visibility Examples**

### **Default Private Behavior**

```limit
frame ConfigManager {
    var config_file: string = "config.json"  // private - no modifier
    var loaded_config: Config                // private - no modifier
    
    fn load_from_disk(): Config {  // private method - no modifier
        return parse_json(read_file(config_file))
    }
    
    pub fn get_config(): Config {  // public - explicit modifier
        if loaded_config == null {
            loaded_config = load_from_disk()
        }
        return loaded_config
    }
}
```

### **Protected for Trait Access**

```limit
trait Configurable {
    fn get_config(): Config
}

frame Service : Configurable {
    var secret_key: string    // private - only Service can access
    prot var config: Config   // protected - trait methods can access
    pub var status: string    // public - anyone can access
    
    pub fn get_config(): Config {
        return self.config  // ✅ trait method accessing protected field
    }
    
    fn internal_setup() {  // private method
        secret_key = generate_key()
        config = load_config()
    }
}
```

---

## **11. Concurrency Model Comparison**

| Model | Syntax | Memory Model | Use Case | Bounded? | Input |
|-------|--------|--------------|----------|----------|-------|
| **Parallel** | `iter(i in range)` | SharedCell (atomic) | CPU-bound computation | ✅ Yes | Range/array |
| **Concurrent (batch)** | `task(i in range)` | Channels + atomic | I/O-bound batch work | ✅ Yes | Range/array |
| **Concurrent (stream)** | `worker(event)` | Channels + atomic | Continuous I/O streams | ❌ No | Event stream |

**When to use each:**

- **Parallel**: Heavy CPU computation, data parallelism, matrix operations
  ```limit
  parallel { iter(i in 0..1000000) { compute_pi(i) } }
  ```

- **Concurrent (batch)**: Database queries, file I/O, network requests over known dataset
  ```limit
  concurrent(mode=batch) { task(id in user_ids) { fetch_user(id) } }
  ```

- **Concurrent (stream)**: WebSocket handlers, message queues, real-time data processing
  ```limit
  concurrent(events: websocket, mode=stream) { worker(msg) { handle_ws(msg) } }
  ```

---

## **12. Summary**

### **Core Principles:**
1. **Composition over inheritance** (no class hierarchies)
2. **Traits for polymorphism** (flexible contracts)
3. **Default private visibility** (no need for `private` keyword)
4. **Three concurrency models:**
   - **Parallel**: Direct `iter()` with SharedCell (CPU-bound)
   - **Concurrent (batch)**: `task()` with channels (bounded I/O)
   - **Concurrent (stream)**: `worker()` with channels (unbounded I/O)
5. **Guaranteed cleanup** (deterministic destruction)
6. **Sequential by default** (opt-in concurrency)

### **Production-Ready Features:**
✅ Full encapsulation (default private, `prot`, `pub`)  
✅ Trait-based polymorphism (static + dynamic)  
✅ Automatic resource management  
✅ Compile-time concurrency safety  
✅ Three clear concurrency models  
✅ Cross-mode composition  
✅ Error resilience  
✅ Channel auto-closing  

