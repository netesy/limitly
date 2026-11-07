# API Documentation: `dns.lm`

## Overview

std/net/dns.lm
DNS resolution and IP address validation module.

## Symbols

- **Frame**: [`DNSError`](#DNSError)
- **Frame**: [`DNSRecord`](#DNSRecord)
- **Frame**: [`Resolver`](#Resolver)
- **Frame**: [`DNS`](#DNS)
- **Function**: [`resolve`](#resolve)
- **Function**: [`resolve_all`](#resolve_all)
- **Function**: [`lookup`](#lookup)
- **Function**: [`resolve_or_passthrough`](#resolve_or_passthrough)
- **Function**: [`reverse_lookup`](#reverse_lookup)
- **Function**: [`is_ip`](#is_ip)
- **Function**: [`is_ipv4`](#is_ipv4)
- **Function**: [`parse_ipv4`](#parse_ipv4)
- **Function**: [`format_ipv4`](#format_ipv4)
- **Function**: [`is_ipv6`](#is_ipv6)
- **Function**: [`is_loopback`](#is_loopback)
- **Function**: [`is_private`](#is_private)
- **Function**: [`is_multicast`](#is_multicast)
- **Function**: [`split_string`](#split_string)
- **Function**: [`is_digit`](#is_digit)
- **Function**: [`is_hex_digit`](#is_hex_digit)

---

### `DNSError` <a id="DNSError"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DNSError
```

Represents an error encountered during DNS resolution or IP parsing.

#### Members

- `var pub code: str` *(field)*
- `var pub message: str` *(field)*
- `pub init(code: str, message: str)` *(constructor)*

---

### `DNSRecord` <a id="DNSRecord"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DNSRecord
```

Represents a single DNS resource record returned from resolution queries.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Use standard record types ("A", "AAAA", "CNAME", "TXT") for consistent protocol handling.

> [!NOTE]
> **Note**: Instances are immutable value containers representing point-in-time DNS state.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `name` | The domain name or fully-qualified domain name (FQDN). |
| `record_type` | The DNS record type identifier (e.g. "A", "AAAA", "TXT"). Default is "A". |
| `value` | The resolved IP address or text payload. Default is empty string. |
| `ttl` | Time-to-live in seconds for caching policies. Default is 300. |

#### Example: Idiomatic Usage

```lymar
var rec = DNSRecord("example.com", "A", "93.184.216.34", 300);
print("Record: {rec.name} -> {rec.value} (TTL: {rec.ttl}s)");
```

#### Members

- `var pub name: str` *(field)*
- `var pub record_type: str` *(field)*
- `var pub value: str` *(field)*
- `var pub ttl: int` *(field)*
- `pub init(name: str)` *(constructor)*

---

### `Resolver` <a id="Resolver"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame Resolver
```

In-memory caching DNS resolver with configurable query timeouts.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Reusing a single `Resolver` instance across worker tasks avoids redundant round-trips to upstream DNS nameservers by utilizing its internal cache.

> [!WARNING]
> **Warning**: Clear cache periodically with `clear_cache()` in long-running processes to honor TTL expirations and dynamic IP updates.

> [!NOTE]
> **Note**: Thread-safe within cooperative async event loops; allocates cached strings on lookup.

#### Example: Idiomatic Usage

```lymar
var resolver = Resolver(timeout=3000);
var ip = resolver.resolve("example.com")? else {
    print("Resolution failed: {err}");
    return;
};
print("Resolved IP: {ip}");
```

#### Members

- `var pub cache: dict` *(field)*
- `var pub timeout_ms: int` *(field)*
- `pub init()` *(constructor)*
- `pub fn resolve(host: str): str` *(method)*
- `pub fn resolve_all(host: str): list` *(method)*
- `pub fn resolve_or_passthrough(host: str): str` *(method)*
- `pub fn reverse_lookup(ip: str): str` *(method)*
- `pub fn clear_cache(): nil` *(method)*

---

### `DNS` <a id="DNS"></a>

**Kind**: Frame  
**Visibility**: `pub`  

```lymar
frame DNS
```

Static namespace wrapper providing convenient DNS resolution and IP address validation.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Call static methods directly via `dns.resolve(host)` or `DNS.resolve(host)`.

> [!NOTE]
> **Note**: Relies on the underlying system socket resolver mechanisms.

#### Example: Idiomatic Usage

```lymar
import std.net.dns as dns;
if (dns.is_ipv4("192.168.1.1")) {
    print("Valid IPv4 gateway");
}
```

#### Members

- `pub init()` *(constructor)*
- `pub fn resolve(host: str): str` *(method)*
- `pub fn resolve_all(host: str): list` *(method)*
- `pub fn lookup(host: str): str` *(method)*
- `pub fn is_ip(address: str): bool` *(method)*
- `pub fn is_ipv4(address: str): bool` *(method)*
- `pub fn is_ipv6(address: str): bool` *(method)*
- `pub fn is_loopback(address: str): bool` *(method)*
- `pub fn is_private(address: str): bool` *(method)*
- `pub fn is_multicast(address: str): bool` *(method)*
- `pub fn parse_ipv4(address: str): list?` *(method)*
- `pub fn format_ipv4(octets: list): str` *(method)*
- `pub fn resolve_or_passthrough(host: str): str` *(method)*
- `pub fn reverse_lookup(ip: str): str` *(method)*

---

### `resolve` <a id="resolve"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn resolve(host: str): str?
```

Resolves a hostname into an IPv4 or IPv6 address using the system DNS resolver.

> [!TIP]
> **Idiomatic Usage & Best Practice**: For applications handling mixed IP/hostname inputs, prefer `resolve_or_passthrough` to eliminate redundant resolution overhead.

> [!WARNING]
> **Warning**: This is a blocking network call bounded by socket resolver timeouts.

> [!NOTE]
> **Note**: Resolves through standard OS name resolution services (`getaddrinfo`).

#### Preconditions (Contracts)

- `requires len(host) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `host` | The domain name or FQDN to query. |

#### Returns

Returns ok(ip_str) on success, or err(DNSError) on DNS failure.

#### Example: Idiomatic Usage

```lymar
var ip = resolve("localhost")? else {
    print("Could not resolve: {err}");
    return;
};
print("Resolved localhost: {ip}");
```

---

### `resolve_all` <a id="resolve_all"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn resolve_all(host: str): list?
```

Resolves a hostname and returns all available IP addresses as a list.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Useful for client-side load balancing, round-robin dispatch, and failover topologies.

#### Preconditions (Contracts)

- `requires len(host) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `host` | The domain name or FQDN to query. |

#### Returns

Returns ok([ip_str]) on success, or err(DNSError) on DNS failure.

#### Example: Idiomatic Usage

```lymar
var ips = resolve_all("localhost")? else {
    print("Resolution error: {err}");
    return;
};
print("Found {len(ips)} IP addresses");
```

---

### `lookup` <a id="lookup"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn lookup(host: str): str?
```

Convenience lookup function; alias for `resolve(host)`.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Standard idiom for simple single-IP DNS resolution.

#### Preconditions (Contracts)

- `requires len(host) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `host` | The domain name or FQDN to query. |

#### Returns

Returns ok(ip_str) on success, or err(DNSError) on DNS failure.

---

### `resolve_or_passthrough` <a id="resolve_or_passthrough"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn resolve_or_passthrough(host: str): str?
```

Returns the host as-is if already an IP address, or resolves it via DNS.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Optimal for HTTP clients and socket connection logic that accept both raw IP addresses (e.g. "127.0.0.1") and hostnames (e.g. "api.service.com").

#### Preconditions (Contracts)

- `requires len(host) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `host` | The candidate hostname or IP address. |

#### Returns

Returns ok(ip_str) on success, or err(DNSError) on failure.

#### Example: Idiomatic Usage

```lymar
var ip1 = resolve_or_passthrough("192.168.1.100")?; // No DNS query
var ip2 = resolve_or_passthrough("localhost")?;     // Resolves to 127.0.0.1
```

---

### `reverse_lookup` <a id="reverse_lookup"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn reverse_lookup(ip: str): str?
```

Performs a reverse DNS lookup to find the canonical hostname corresponding to an IP.

> [!WARNING]
> **Warning**: If no reverse PTR mapping exists, this may return the IP address itself.

#### Preconditions (Contracts)

- `requires len(ip) > 0`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `ip` | A valid IPv4 or IPv6 address string. |

#### Returns

Returns ok(hostname) on success, or err(DNSError) if the IP syntax is invalid.

#### Example: Idiomatic Usage

```lymar
var host = reverse_lookup("127.0.0.1")?;
print("Host: {host}"); // "localhost"
```

---

### `is_ip` <a id="is_ip"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_ip(address: str): bool
```

Checks whether the provided string is a valid IPv4 or IPv6 address.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Fast local syntactic validation that incurs zero network or DNS overhead.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The candidate IP address string to check. |

#### Returns

Returns true if the address is a valid IPv4 or IPv6 format, false otherwise.

#### Example: Idiomatic Usage

```lymar
print("Is IP: {is_ip(\"10.0.0.1\")}"); // true
print("Is IP: {is_ip(\"example.com\")}"); // false
```

---

### `is_ipv4` <a id="is_ipv4"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_ipv4(address: str): bool
```

Validates whether a string strictly conforms to IPv4 dotted-quad notation.

> [!NOTE]
> **Note**: Rejects leading zeroes (e.g. "01"), out-of-range octets (> 255), and negative numbers.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The candidate string to inspect. |

#### Returns

Returns true if strictly valid IPv4, false otherwise.

#### Example: Idiomatic Usage

```lymar
print("Valid: {is_ipv4(\"172.16.254.1\")}"); // true
print("Valid: {is_ipv4(\"256.0.0.1\")}");     // false
```

---

### `parse_ipv4` <a id="parse_ipv4"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn parse_ipv4(address: str): list?
```

Parses an IPv4 dotted string into a list of 4 integer octets [0-255].

> [!TIP]
> **Idiomatic Usage & Best Practice**: Useful for binary subnet mask arithmetic, CIDR matching, and network telemetry.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The candidate IPv4 string to parse. |

#### Returns

Returns ok([o0, o1, o2, o3]) on success, or nil if invalid IPv4 syntax.

#### Example: Idiomatic Usage

```lymar
var octets = parse_ipv4("192.168.1.1");
if (octets != nil) {
    var o = octets as [int];
    print("First octet: {o[0]}"); // 192
}
```

---

### `format_ipv4` <a id="format_ipv4"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn format_ipv4(octets: list): str
```

Formats a list of 4 integer octets into a canonical IPv4 dotted-quad string.

#### Preconditions (Contracts)

- `requires len(octets) == 4`

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `octets` | An array containing exactly 4 integer octets (0-255). |

#### Returns

Formatted dotted-decimal IPv4 string, or empty string on length mismatch.

#### Example: Idiomatic Usage

```lymar
var ip_str = format_ipv4([127, 0, 0, 1]);
print("Formatted IP: {ip_str}"); // "127.0.0.1"
```

---

### `is_ipv6` <a id="is_ipv6"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_ipv6(address: str): bool
```

Validates whether a string conforms to IPv6 hexadecimal notation.

> [!NOTE]
> **Note**: Recognizes standard 8-group notation and `::` zero-compaction (RFC 4291).

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The candidate string to inspect. |

#### Returns

Returns true if valid IPv6 format, false otherwise.

#### Example: Idiomatic Usage

```lymar
print("Valid IPv6: {is_ipv6(\"2001:db8::1\")}"); // true
print("Valid IPv6: {is_ipv6(\"::1\")}");          // true
```

---

### `is_loopback` <a id="is_loopback"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_loopback(address: str): bool
```

Checks whether an IP address belongs to the loopback interface range.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Correctly handles IPv4 127.0.0.0/8 subnet and IPv6 ::1 loopback representation.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The IPv4 or IPv6 address to verify. |

#### Returns

Returns true if loopback, false otherwise.

#### Example: Idiomatic Usage

```lymar
print("Loopback: {is_loopback(\"127.0.0.1\")}"); // true
print("Loopback: {is_loopback(\"::1\")}");       // true
```

---

### `is_private` <a id="is_private"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_private(address: str): bool
```

Checks whether an IP address belongs to private or link-local network ranges.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Evaluates RFC 1918 private subnets (10.0.0.0/8, 172.16.0.0/12, 192.168.0.0/16), RFC 3927 link-local (169.254.0.0/16), loopback, and IPv6 ULA (fc00::/7) / link-local (fe80::/10).

> [!WARNING]
> **Warning**: Useful for SSRF protection and validating that user-supplied URLs do not target internal networks.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The IP address string to inspect. |

#### Returns

Returns true if private or link-local, false if publicly routable.

#### Example: Idiomatic Usage

```lymar
if (is_private("192.168.1.1")) {
    print("Internal network address");
}
```

---

### `is_multicast` <a id="is_multicast"></a>

**Kind**: Function  
**Visibility**: `pub`  

```lymar
pub fn is_multicast(address: str): bool
```

Checks whether an address is within the Class D (IPv4) or IPv6 multicast range.

> [!TIP]
> **Idiomatic Usage & Best Practice**: Detects IPv4 224.0.0.0 to 239.255.255.255 and IPv6 ff00::/8.

#### Parameters

| Parameter | Description |
| :--- | :--- |
| `address` | The IP address string to check. |

#### Returns

Returns true if multicast, false otherwise.

#### Example: Idiomatic Usage

```lymar
print("Multicast: {is_multicast(\"224.0.0.1\")}"); // true
```

---

### `split_string` <a id="split_string"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn split_string(s: str, delimiter: str): list
```

---

### `is_digit` <a id="is_digit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_digit(ch: str): bool
```

---

### `is_hex_digit` <a id="is_hex_digit"></a>

**Kind**: Function  
**Visibility**: `private`  

```lymar
fn is_hex_digit(ch: str): bool
```

---

