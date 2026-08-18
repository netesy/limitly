.section .data
.align 8
heap_ptr:
  .quad __fyra_heap
.section .bss
.align 16
__fyra_heap:
  .zero 1048576
.text

.data
.align 16
__heap_base:
  .zero 1048576
.align 8
__heap_ptr:
  .quad __heap_base
.align 8
str_const_0:
  .string ""
.align 8
str_const_1:
  .string " "
.align 8
str_const_2:
  .string "%20"
.align 8
str_const_3:
  .string "/"
.align 8
str_const_4:
  .string "%2"
.align 8
str_const_5:
  .string "F"
.align 8
str_const_6:
  .string ":"
.align 8
str_const_7:
  .string "%3"
.align 8
str_const_8:
  .string "A"
.align 8
str_const_9:
  .string "?"
.align 8
str_const_10:
  .string "%3"
.align 8
str_const_11:
  .string "F"
.align 8
str_const_12:
  .string "="
.align 8
str_const_13:
  .string "%3"
.align 8
str_const_14:
  .string "D"
.align 8
str_const_15:
  .string "&"
.align 8
str_const_16:
  .string "%26"
.align 8
str_const_17:
  .string "%"
.align 8
str_const_18:
  .string "%25"
.align 8
str_const_19:
  .string "+"
.align 8
str_const_20:
  .string "%2"
.align 8
str_const_21:
  .string "B"
.align 8
str_const_22:
  .string "#"
.align 8
str_const_23:
  .string "%23"
.align 8
str_const_24:
  .string "=== URL Module Test Suite ==="
.align 8
str_const_25:
  .string "Parsing tests failed"
.align 8
str_const_26:
  .string "Query params tests failed"
.align 8
str_const_27:
  .string "Builder tests failed"
.align 8
str_const_28:
  .string "All URL tests completed successfully."
.align 8
str_const_29:
  .string "Running URLBuilder tests..."
.align 8
str_const_30:
  .string "https"
.align 8
str_const_31:
  .string "example.org"
.align 8
str_const_32:
  .string "/api/v1/resource"
.align 8
str_const_33:
  .string "active=true"
.align 8
str_const_34:
  .string "details"
.align 8
str_const_35:
  .string "https"
.align 8
str_const_36:
  .string "builder.build() scheme incorrect"
.align 8
str_const_37:
  .string "example.org"
.align 8
str_const_38:
  .string "builder.build() host incorrect"
.align 8
str_const_39:
  .string "builder.build() port incorrect"
.align 8
str_const_40:
  .string "/api/v1/resource"
.align 8
str_const_41:
  .string "builder.build() path incorrect"
.align 8
str_const_42:
  .string "active=true"
.align 8
str_const_43:
  .string "builder.build() query incorrect"
.align 8
str_const_44:
  .string "details"
.align 8
str_const_45:
  .string "builder.build() fragment incorrect"
.align 8
str_const_46:
  .string "https://example.org:9000/api/v1/resource?active=true#details"
.align 8
str_const_47:
  .string "serialized incorrect: "
.align 8
str_const_48:
  .string "URLBuilder tests passed!"
.align 8
str_const_49:
  .string ""
.align 8
str_const_50:
  .string ""
.align 8
str_const_51:
  .string "Running URL query parameters tests..."
.align 8
str_const_52:
  .string "a=1&b=2&a=3&c=special%20value&empty="
.align 8
str_const_53:
  .string "a"
.align 8
str_const_54:
  .string "1"
.align 8
str_const_55:
  .string "qp.get('a') should return first value '1'"
.align 8
str_const_56:
  .string "b"
.align 8
str_const_57:
  .string "2"
.align 8
str_const_58:
  .string "qp.get('b') should return '2'"
.align 8
str_const_59:
  .string "c"
.align 8
str_const_60:
  .string "special value"
.align 8
str_const_61:
  .string "qp.get('c') should be decoded 'special value'"
.align 8
str_const_62:
  .string "empty"
.align 8
str_const_63:
  .string ""
.align 8
str_const_64:
  .string "qp.get('empty') should be empty string"
.align 8
str_const_65:
  .string "nonexistent"
.align 8
str_const_66:
  .string ""
.align 8
str_const_67:
  .string "qp.get('nonexistent') should be empty string"
.align 8
str_const_68:
  .string "a"
.align 8
str_const_69:
  .string "qp.get_all('a') should return list of length 2"
.align 8
str_const_70:
  .string "1"
.align 8
str_const_71:
  .string "a_all[0] should be '1'"
.align 8
str_const_72:
  .string "3"
.align 8
str_const_73:
  .string "a_all[1] should be '3'"
.align 8
str_const_74:
  .string "b"
.align 8
str_const_75:
  .string "qp.has('b') should be true"
.align 8
str_const_76:
  .string "xyz"
.align 8
str_const_77:
  .string "qp.has('xyz') should be false"
.align 8
str_const_78:
  .string "b"
.align 8
str_const_79:
  .string "99"
.align 8
str_const_80:
  .string "b"
.align 8
str_const_81:
  .string "99"
.align 8
str_const_82:
  .string "qp.set('b', '99') failed"
.align 8
str_const_83:
  .string "d"
.align 8
str_const_84:
  .string "new"
.align 8
str_const_85:
  .string "d"
.align 8
str_const_86:
  .string "new"
.align 8
str_const_87:
  .string "qp.add('d', 'new') failed"
.align 8
str_const_88:
  .string "a"
.align 8
str_const_89:
  .string "a"
.align 8
str_const_90:
  .string "qp.remove('a') failed to remove 'a'"
.align 8
str_const_91:
  .string "b=99&c=special%20value&empty=&d=new"
.align 8
str_const_92:
  .string "qp.to_string() failed: "
.align 8
str_const_93:
  .string "Query parameters tests passed!"
.align 8
str_const_94:
  .string ""
.align 8
str_const_95:
  .string "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
.align 8
str_const_96:
  .string "abcdefghijklmnopqrstuvwxyz"
.align 8
str_const_97:
  .string ""
.align 8
str_const_98:
  .string "%"
.align 8
str_const_99:
  .string "20"
.align 8
str_const_100:
  .string " "
.align 8
str_const_101:
  .string "2"
.align 8
str_const_102:
  .string "F"
.align 8
str_const_103:
  .string "/"
.align 8
str_const_104:
  .string "2"
.align 8
str_const_105:
  .string "f"
.align 8
str_const_106:
  .string "/"
.align 8
str_const_107:
  .string "3"
.align 8
str_const_108:
  .string "A"
.align 8
str_const_109:
  .string ":"
.align 8
str_const_110:
  .string "3"
.align 8
str_const_111:
  .string "a"
.align 8
str_const_112:
  .string ":"
.align 8
str_const_113:
  .string "3"
.align 8
str_const_114:
  .string "F"
.align 8
str_const_115:
  .string "?"
.align 8
str_const_116:
  .string "3"
.align 8
str_const_117:
  .string "f"
.align 8
str_const_118:
  .string "?"
.align 8
str_const_119:
  .string "3"
.align 8
str_const_120:
  .string "D"
.align 8
str_const_121:
  .string "="
.align 8
str_const_122:
  .string "3"
.align 8
str_const_123:
  .string "d"
.align 8
str_const_124:
  .string "="
.align 8
str_const_125:
  .string "26"
.align 8
str_const_126:
  .string "&"
.align 8
str_const_127:
  .string "25"
.align 8
str_const_128:
  .string "%"
.align 8
str_const_129:
  .string "2"
.align 8
str_const_130:
  .string "B"
.align 8
str_const_131:
  .string "+"
.align 8
str_const_132:
  .string "2"
.align 8
str_const_133:
  .string "b"
.align 8
str_const_134:
  .string "+"
.align 8
str_const_135:
  .string "23"
.align 8
str_const_136:
  .string "#"
.align 8
str_const_137:
  .string "%"
.align 8
str_const_138:
  .string ""
.align 8
str_const_139:
  .string ""
.align 8
str_const_140:
  .string ""
.align 8
str_const_141:
  .string ""
.align 8
str_const_142:
  .string "/"
.align 8
str_const_143:
  .string ""
.align 8
str_const_144:
  .string "."
.align 8
str_const_145:
  .string ".."
.align 8
str_const_146:
  .string ""
.align 8
str_const_147:
  .string "/"
.align 8
str_const_148:
  .string "/"
.align 8
str_const_149:
  .string "/"
.align 8
str_const_150:
  .string ""
.align 8
str_const_151:
  .string ""
.align 8
str_const_152:
  .string ""
.align 8
str_const_153:
  .string "&"
.align 8
str_const_154:
  .string ""
.align 8
str_const_155:
  .string "="
.align 8
str_const_156:
  .string ""
.align 8
str_const_157:
  .string "Running URL parsing tests..."
.align 8
str_const_158:
  .string "http://example.com/path/to/page?query=1#frag"
.align 8
str_const_159:
  .string "http"
.align 8
str_const_160:
  .string "u1.scheme should be http"
.align 8
str_const_161:
  .string "example.com"
.align 8
str_const_162:
  .string "u1.host should be example.com"
.align 8
str_const_163:
  .string "u1.port should be 80"
.align 8
str_const_164:
  .string "/path/to/page"
.align 8
str_const_165:
  .string "u1.path should be /path/to/page"
.align 8
str_const_166:
  .string "query=1"
.align 8
str_const_167:
  .string "u1.query should be query=1"
.align 8
str_const_168:
  .string "frag"
.align 8
str_const_169:
  .string "u1.fragment should be frag"
.align 8
str_const_170:
  .string "u1.is_valid should be true"
.align 8
str_const_171:
  .string "https://secure.example.org:8443/"
.align 8
str_const_172:
  .string "https"
.align 8
str_const_173:
  .string "u2.scheme should be https"
.align 8
str_const_174:
  .string "secure.example.org"
.align 8
str_const_175:
  .string "u2.host should be secure.example.org"
.align 8
str_const_176:
  .string "u2.port should be 8443"
.align 8
str_const_177:
  .string "/"
.align 8
str_const_178:
  .string "u2.path should be /"
.align 8
str_const_179:
  .string "ftp://user:pass@ftp.example.com/dir/file.txt"
.align 8
str_const_180:
  .string "ftp"
.align 8
str_const_181:
  .string "u3.scheme should be ftp"
.align 8
str_const_182:
  .string "user"
.align 8
str_const_183:
  .string "u3.username should be user"
.align 8
str_const_184:
  .string "pass"
.align 8
str_const_185:
  .string "u3.password should be pass"
.align 8
str_const_186:
  .string "ftp.example.com"
.align 8
str_const_187:
  .string "u3.host should be ftp.example.com"
.align 8
str_const_188:
  .string "/dir/file.txt"
.align 8
str_const_189:
  .string "u3.path should be /dir/file.txt"
.align 8
str_const_190:
  .string "http://[2001:db8::1]:8080/index.html"
.align 8
str_const_191:
  .string "http"
.align 8
str_const_192:
  .string "u4.scheme should be http"
.align 8
str_const_193:
  .string "[2001:db8::1]"
.align 8
str_const_194:
  .string "u4.host should be [2001:db8::1]"
.align 8
str_const_195:
  .string "u4.port should be 8080"
.align 8
str_const_196:
  .string "/new-path?new-query#new-frag"
.align 8
str_const_197:
  .string "Resolved path: %s"
.align 8
str_const_198:
  .string "Resolved query: %s"
.align 8
str_const_199:
  .string "Resolved fragment: %s"
.align 8
str_const_200:
  .string "http"
.align 8
str_const_201:
  .string "resolved.scheme should be http"
.align 8
str_const_202:
  .string "example.com"
.align 8
str_const_203:
  .string "resolved.host should be example.com"
.align 8
str_const_204:
  .string "/new-path"
.align 8
str_const_205:
  .string "resolved.path should be /new-path"
.align 8
str_const_206:
  .string "new-query"
.align 8
str_const_207:
  .string "resolved.query should be new-query"
.align 8
str_const_208:
  .string "new-frag"
.align 8
str_const_209:
  .string "resolved.fragment should be new-frag"
.align 8
str_const_210:
  .string "http://example.com"
.align 8
str_const_211:
  .string "u1.origin() failed"
.align 8
str_const_212:
  .string "https://secure.example.org:8443"
.align 8
str_const_213:
  .string "u2.origin() failed"
.align 8
str_const_214:
  .string "Parsing tests passed!"
.align 8
nl:
  .string "
"
.align 8
assert_fail:
  .string "Assertion failed
"
.text
.globl main
.globl _start
_start:
  and %rsp, -16
  and rsp, -16
  subq $32, %rsp
  call main
  addq $32, %rsp
  mov rcx, rax
  subq $32, %rsp
  call ExitProcess
  addq $32, %rsp

.globl main
main:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 152
main_entry:
main_block_0:
  call std.url.index.__init__
  call std.url.url.__init__
  call std.url.query.__init__
  call std.url.builder.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  call test_parsing
  movq $r2, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_query_params
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_builder
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  addq $16, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  mov rax, [rax]
  movq rax, [rbp + -168]
  movq [rbp + -168], rcx
  call lm_print_str
  movq $1, rax
  jmp main_epilogue
main_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_main:

.globl std.url.index.__init__
std.url.index.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.url.index.__init___entry:
  movq $0, rax
  jmp std.url.index.__init___epilogue
std.url.index.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.__init__:

.globl std.url.index.parse
std.url.index.parse:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.index.parse_entry:
std.url.index.parse_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.url.url.URL.init
  movq [rbp + -72], rax
  jmp std.url.index.parse_epilogue
std.url.index.parse_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.parse:

.globl std.url.index.QueryParams
std.url.index.QueryParams:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.url.index.QueryParams_entry:
std.url.index.QueryParams_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.url.query.QueryParams.init
  movq $0, rax
  jmp std.url.index.QueryParams_epilogue
std.url.index.QueryParams_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.QueryParams:

.globl std.url.index.URL
std.url.index.URL:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.index.URL_entry:
std.url.index.URL_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  movq [rbp + -64], rdx
  call std.url.url.URL.init
  movq [rbp + -72], rax
  jmp std.url.index.URL_epilogue
std.url.index.URL_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.URL:

.globl std.url.index.parse_query
std.url.index.parse_query:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.index.parse_query_entry:
std.url.index.parse_query_block_0:
  movq [rbp + -64], rcx
  call std.url.query.parse
  movq $r1, rax
  jmp std.url.index.parse_query_epilogue
std.url.index.parse_query_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.parse_query:

.globl std.url.builder.URLBuilder.init
std.url.builder.URLBuilder.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.builder.URLBuilder.init_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.init_epilogue
std.url.builder.URLBuilder.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.init:

.globl std.url.url.URL.resolve
std.url.url.URL.resolve:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.url.URL.resolve_entry:
  movq $0, rax
  jmp std.url.url.URL.resolve_epilogue
std.url.url.URL.resolve_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.URL.resolve:

.globl std.url.query.QueryParams.set
std.url.query.QueryParams.set:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.url.query.QueryParams.set_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.set_epilogue
std.url.query.QueryParams.set_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.set:

.globl std.encoding.percent.encode
std.encoding.percent.encode:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 456
  mov [rbp + -64], rcx
std.encoding.percent.encode_entry:
std.encoding.percent.encode_block_0:
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.encoding.percent.encode_block_5
std.encoding.percent.encode_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_7
  jmp std.encoding.percent.encode_block_101
std.encoding.percent.encode_block_7:
  jmp std.encoding.percent.encode_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r10, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_15
  jmp std.encoding.percent.encode_block_19
std.encoding.percent.encode_block_15:
  jmp std.encoding.percent.encode_block_15
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -72], rcx
  movq [rbp + -112], rdx
  call lm_str_concat
  movq rax, [rbp + -120]
  jmp std.encoding.percent.encode_block_96
std.encoding.percent.encode_block_19:
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r10, rax
  cmpq [rbp + -128], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_22
  jmp std.encoding.percent.encode_block_28
std.encoding.percent.encode_block_22:
  jmp std.encoding.percent.encode_block_22
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -120], rcx
  movq [rbp + -144], rdx
  call lm_str_concat
  movq rax, [rbp + -152]
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_str_concat
  movq rax, [rbp + -168]
  jmp std.encoding.percent.encode_block_95
std.encoding.percent.encode_block_28:
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r10, rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_31
  jmp std.encoding.percent.encode_block_37
std.encoding.percent.encode_block_31:
  jmp std.encoding.percent.encode_block_31
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -168], rcx
  movq [rbp + -192], rdx
  call lm_str_concat
  movq rax, [rbp + -200]
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -200], rcx
  movq [rbp + -208], rdx
  call lm_str_concat
  movq rax, [rbp + -216]
  jmp std.encoding.percent.encode_block_94
std.encoding.percent.encode_block_37:
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r10, rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rbp + -232], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_40
  jmp std.encoding.percent.encode_block_46
std.encoding.percent.encode_block_40:
  jmp std.encoding.percent.encode_block_40
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -216], rcx
  movq [rbp + -240], rdx
  call lm_str_concat
  movq rax, [rbp + -248]
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_str_concat
  movq rax, [rbp + -264]
  jmp std.encoding.percent.encode_block_93
std.encoding.percent.encode_block_46:
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $r10, rax
  cmpq [rbp + -272], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_49
  jmp std.encoding.percent.encode_block_55
std.encoding.percent.encode_block_49:
  jmp std.encoding.percent.encode_block_49
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -264], rcx
  movq [rbp + -288], rdx
  call lm_str_concat
  movq rax, [rbp + -296]
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rcx
  movq [rbp + -304], rdx
  call lm_str_concat
  movq rax, [rbp + -312]
  jmp std.encoding.percent.encode_block_92
std.encoding.percent.encode_block_55:
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r10, rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rbp + -328], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_58
  jmp std.encoding.percent.encode_block_62
std.encoding.percent.encode_block_58:
  jmp std.encoding.percent.encode_block_58
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -312], rcx
  movq [rbp + -336], rdx
  call lm_str_concat
  movq rax, [rbp + -344]
  jmp std.encoding.percent.encode_block_91
std.encoding.percent.encode_block_62:
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r10, rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_65
  jmp std.encoding.percent.encode_block_69
std.encoding.percent.encode_block_65:
  jmp std.encoding.percent.encode_block_65
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -344], rcx
  movq [rbp + -368], rdx
  call lm_str_concat
  movq rax, [rbp + -376]
  jmp std.encoding.percent.encode_block_90
std.encoding.percent.encode_block_69:
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq $r10, rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_72
  jmp std.encoding.percent.encode_block_78
std.encoding.percent.encode_block_72:
  jmp std.encoding.percent.encode_block_72
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -376], rcx
  movq [rbp + -400], rdx
  call lm_str_concat
  movq rax, [rbp + -408]
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_str_concat
  movq rax, [rbp + -424]
  jmp std.encoding.percent.encode_block_89
std.encoding.percent.encode_block_78:
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq $r10, rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.encoding.percent.encode_block_81
  jmp std.encoding.percent.encode_block_85
std.encoding.percent.encode_block_81:
  jmp std.encoding.percent.encode_block_81
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -424], rcx
  movq [rbp + -448], rdx
  call lm_str_concat
  movq rax, [rbp + -456]
  jmp std.encoding.percent.encode_block_88
std.encoding.percent.encode_block_85:
  movq [rbp + -456], rcx
  movq $r10, rdx
  call lm_str_concat
  movq rax, [rbp + -464]
  jmp std.encoding.percent.encode_block_88
std.encoding.percent.encode_block_88:
  jmp std.encoding.percent.encode_block_89
std.encoding.percent.encode_block_89:
  jmp std.encoding.percent.encode_block_90
std.encoding.percent.encode_block_90:
  jmp std.encoding.percent.encode_block_91
std.encoding.percent.encode_block_91:
  jmp std.encoding.percent.encode_block_92
std.encoding.percent.encode_block_92:
  jmp std.encoding.percent.encode_block_93
std.encoding.percent.encode_block_93:
  jmp std.encoding.percent.encode_block_94
std.encoding.percent.encode_block_94:
  jmp std.encoding.percent.encode_block_95
std.encoding.percent.encode_block_95:
  jmp std.encoding.percent.encode_block_96
std.encoding.percent.encode_block_96:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -472]
  jmp std.encoding.percent.encode_block_5
std.encoding.percent.encode_block_101:
  movq [rbp + -464], rax
  jmp std.encoding.percent.encode_epilogue
std.encoding.percent.encode_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.encoding.percent.encode:

.globl std.url.url.URL.query_params
std.url.url.URL.query_params:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.url.URL.query_params_entry:
  movq $0, rax
  jmp std.url.url.URL.query_params_epilogue
std.url.url.URL.query_params_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.URL.query_params:

.globl std.url.query.build
std.url.query.build:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.query.build_entry:
std.url.query.build_block_0:
  movq [rbp + -64], rcx
  call std.url.query.QueryParams.to_string
  movq $r1, rax
  jmp std.url.query.build_epilogue
std.url.query.build_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.build:

.globl test_builder
test_builder:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 376
test_builder_entry:
test_builder_block_0:
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  call std.url.index.URLBuilder
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call std.url.builder.URLBuilder.set_scheme
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -96], rcx
  movq [rbp + -112], rdx
  call std.url.builder.URLBuilder.set_host
  movq [rbp + -96], rcx
  movq $72001, rdx
  call std.url.builder.URLBuilder.set_port
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  call std.url.builder.URLBuilder.set_path
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -96], rcx
  movq [rbp + -128], rdx
  call std.url.builder.URLBuilder.set_query
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -96], rcx
  movq [rbp + -136], rdx
  call std.url.builder.URLBuilder.set_fragment
  movq [rbp + -96], rcx
  call std.url.builder.URLBuilder.build
  movq $r17, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -144]
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq $r17, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -176]
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq $r17, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  cmpq $72001, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -216], rcx
  movq [rbp + -224], rdx
  call lm_assert
  movq $r17, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -232]
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq $r17, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -264]
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rax
  cmpq [rbp + -272], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq $r17, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -296]
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -296], rax
  cmpq [rbp + -304], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rcx
  movq [rbp + -320], rdx
  call lm_assert
  movq $r17, rcx
  call std.url.url.URL.to_string
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq $r50, rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -344], rcx
  movq $r50, rdx
  call lm_str_concat
  movq rax, [rbp + -352]
  movq [rbp + -336], rcx
  movq [rbp + -352], rdx
  call lm_assert
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -360], rax
  addq $16, rax
  movq rax, [rbp + -368]
  movq [rbp + -368], rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  mov rax, [rax]
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  call lm_print_str
  movq $9, rax
  jmp test_builder_epilogue
test_builder_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_builder:

.globl std.url.builder.__init__
std.url.builder.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.url.builder.__init___entry:
  movq $0, rax
  jmp std.url.builder.__init___epilogue
std.url.builder.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.__init__:

.globl std.url.url.find_last
std.url.url.find_last:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.url.find_last_entry:
std.url.url.find_last_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r2, rax
  subq $9, rax
  movq rax, $r4
  jmp std.url.url.find_last_block_5
std.url.url.find_last_block_5:
  movq $r4, rax
  cmpq $1, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.url.url.find_last_block_8
  jmp std.url.url.find_last_block_19
std.url.url.find_last_block_8:
  jmp std.url.url.find_last_block_8
  movq $r4, rax
  addq $9, rax
  movq rax, $r11
  movq [rbp + -64], rcx
  movq $r4, rdx
  movq $r11, r8
  call substring
  movq $r12, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.url.url.find_last_block_14
  jmp std.url.url.find_last_block_15
std.url.url.find_last_block_14:
  jmp std.url.url.find_last_block_14
  movq $r4, rax
  jmp std.url.url.find_last_epilogue
std.url.url.find_last_block_15:
  movq $r4, rax
  subq $9, rax
  movq rax, $r16
  jmp std.url.url.find_last_block_5
std.url.url.find_last_block_19:
  movq $9, rax
  negq rax
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  jmp std.url.url.find_last_epilogue
std.url.url.find_last_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.find_last:

.globl std.url.url.split_str
std.url.url.split_str:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.url.split_str_entry:
std.url.url.split_str_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.url.url.split_str_block_6
std.url.url.split_str_block_6:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.url.url.split_str_block_9
  jmp std.url.url.split_str_block_32
std.url.url.split_str_block_9:
  jmp std.url.url.split_str_block_9
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r13, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.url.url.split_str_block_15
  jmp std.url.url.split_str_block_19
std.url.url.split_str_block_15:
  jmp std.url.url.split_str_block_15
  movq $r2, rcx
  movq [rbp + -80], rdx
  call lm_list_append
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  jmp std.url.url.split_str_block_27
std.url.url.split_str_block_19:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -120], r8
  call substring
  movq $r22, rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -112], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp std.url.url.split_str_block_27
std.url.url.split_str_block_27:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.url.url.split_str_block_6
std.url.url.split_str_block_32:
  movq $r2, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq $r2, rax
  jmp std.url.url.split_str_epilogue
std.url.url.split_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.split_str:

.globl test_query_params
test_query_params:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 568
test_query_params_entry:
test_query_params_block_0:
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.url.index.parse_query
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -104], rcx
  movq [rbp + -112], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r7, rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -104], rcx
  movq [rbp + -144], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r13, rax
  cmpq [rbp + -152], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -160]
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rcx
  movq [rbp + -168], rdx
  call lm_assert
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -104], rcx
  movq [rbp + -176], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r19, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -104], rcx
  movq [rbp + -208], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r25, rax
  cmpq [rbp + -216], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -104], rcx
  movq [rbp + -240], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $r31, rax
  cmpq [rbp + -248], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -104], rcx
  movq [rbp + -272], rdx
  call std.url.query.QueryParams.get_all
  movq $r37, rcx
  call lm_list_len
  movq $r40, rax
  cmpq $17, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq $r37, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $r46, rax
  cmpq [rbp + -296], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq $r37, rcx
  movq $9, rdx
  call lm_list_get
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r52, rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -104], rcx
  movq [rbp + -344], rdx
  call std.url.query.QueryParams.has
  movq $r58, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq [rbp + -352], rcx
  movq [rbp + -360], rdx
  call lm_assert
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -104], rcx
  movq [rbp + -368], rdx
  call std.url.query.QueryParams.has
  movq $r64, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -376]
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -376], rcx
  movq [rbp + -384], rdx
  call lm_assert
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -104], rcx
  movq [rbp + -392], rdx
  movq [rbp + -400], r8
  call std.url.query.QueryParams.set
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -104], rcx
  movq [rbp + -408], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $r73, rax
  cmpq [rbp + -416], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -424]
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq [rbp + -424], rcx
  movq [rbp + -432], rdx
  call lm_assert
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -104], rcx
  movq [rbp + -440], rdx
  movq [rbp + -448], r8
  call std.url.query.QueryParams.add
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq [rbp + -104], rcx
  movq [rbp + -456], rdx
  call std.url.query.QueryParams.get
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq $r82, rax
  cmpq [rbp + -464], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -472]
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq [rbp + -472], rcx
  movq [rbp + -480], rdx
  call lm_assert
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq [rbp + -104], rcx
  movq [rbp + -488], rdx
  call std.url.query.QueryParams.remove
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -104], rcx
  movq [rbp + -496], rdx
  call std.url.query.QueryParams.has
  movq $r90, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -504]
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq [rbp + -504], rcx
  movq [rbp + -512], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.url.query.QueryParams.to_string
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq $r95, rax
  cmpq [rbp + -520], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -528]
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq [rbp + -536], rcx
  movq $r95, rdx
  call lm_str_concat
  movq rax, [rbp + -544]
  movq [rbp + -528], rcx
  movq [rbp + -544], rdx
  call lm_assert
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  addq $16, rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  mov rax, [rax]
  movq rax, [rbp + -576]
  movq [rbp + -576], rcx
  call lm_print_str
  movq $9, rax
  jmp test_query_params_epilogue
test_query_params_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_query_params:

.globl std.url.query.__init__
std.url.query.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.url.query.__init___entry:
  movq $0, rax
  jmp std.url.query.__init___epilogue
std.url.query.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.__init__:

.globl std.url.url.to_lower
std.url.url.to_lower:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
std.url.url.to_lower_entry:
std.url.url.to_lower_block_0:
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  jmp std.url.url.to_lower_block_5
std.url.url.to_lower_block_5:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.url.url.to_lower_block_8
  jmp std.url.url.to_lower_block_35
std.url.url.to_lower_block_8:
  jmp std.url.url.to_lower_block_8
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rbp + -80], rcx
  movq $r11, rdx
  call std.url.url.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq $r13, rax
  cmpq [rbp + -112], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.url.url.to_lower_block_19
  jmp std.url.url.to_lower_block_27
std.url.url.to_lower_block_19:
  jmp std.url.url.to_lower_block_19
  movq $r13, rax
  addq $9, rax
  movq rax, $r21
  movq [rbp + -88], rcx
  movq $r13, rdx
  movq $r21, r8
  call substring
  movq $r22, rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -72], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp std.url.url.to_lower_block_30
std.url.url.to_lower_block_27:
  movq [rbp + -136], rcx
  movq $r11, rdx
  call lm_str_concat
  movq rax, [rbp + -144]
  jmp std.url.url.to_lower_block_30
std.url.url.to_lower_block_30:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.url.url.to_lower_block_5
std.url.url.to_lower_block_35:
  movq [rbp + -144], rax
  jmp std.url.url.to_lower_epilogue
std.url.url.to_lower_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.to_lower:

.globl std.encoding.percent.__init__
std.encoding.percent.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.encoding.percent.__init___entry:
  movq $0, rax
  jmp std.encoding.percent.__init___epilogue
std.encoding.percent.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.encoding.percent.__init__:

.globl std.url.index.URLBuilder
std.url.index.URLBuilder:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
std.url.index.URLBuilder_entry:
std.url.index.URLBuilder_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.url.builder.URLBuilder.init
  movq $0, rax
  jmp std.url.index.URLBuilder_epilogue
std.url.index.URLBuilder_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.URLBuilder:

.globl std.url.query.QueryParams.add
std.url.query.QueryParams.add:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.url.query.QueryParams.add_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.add_epilogue
std.url.query.QueryParams.add_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.add:

.globl std.url.index.build
std.url.index.build:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 88
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.url.index.build_entry:
std.url.index.build_block_0:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq [rbp + -80], r8
  movq [rbp + -88], r9
  call std.url.url.build
  movq $r6, rax
  jmp std.url.index.build_epilogue
std.url.index.build_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.index.build:

.globl std.url.url.URL.origin
std.url.url.URL.origin:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.url.URL.origin_entry:
  movq $0, rax
  jmp std.url.url.URL.origin_epilogue
std.url.url.URL.origin_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.URL.origin:

.globl std.url.url.URL.parse
std.url.url.URL.parse:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.url.URL.parse_entry:
  movq $0, rax
  jmp std.url.url.URL.parse_epilogue
std.url.url.URL.parse_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.URL.parse:

.globl std.url.url.URL.init
std.url.url.URL.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.url.URL.init_entry:
  movq $0, rax
  jmp std.url.url.URL.init_epilogue
std.url.url.URL.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.URL.init:

.globl std.url.builder.URLBuilder.set_query
std.url.builder.URLBuilder.set_query:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_query_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_query_epilogue
std.url.builder.URLBuilder.set_query_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_query:

.globl std.url.builder.URLBuilder.set_path
std.url.builder.URLBuilder.set_path:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_path_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_path_epilogue
std.url.builder.URLBuilder.set_path_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_path:

.globl std.url.url.URL.to_string
std.url.url.URL.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.url.URL.to_string_entry:
  movq $0, rax
  jmp std.url.url.URL.to_string_epilogue
std.url.url.URL.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.URL.to_string:

.globl std.url.builder.URLBuilder.set_scheme
std.url.builder.URLBuilder.set_scheme:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_scheme_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_scheme_epilogue
std.url.builder.URLBuilder.set_scheme_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_scheme:

.globl std.encoding.percent.decode
std.encoding.percent.decode:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 776
  mov [rbp + -64], rcx
std.encoding.percent.decode_entry:
std.encoding.percent.decode_block_0:
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  call lm_list_len
  jmp std.encoding.percent.decode_block_5
std.encoding.percent.decode_block_5:
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_7
  jmp std.encoding.percent.decode_block_180
std.encoding.percent.decode_block_7:
  jmp std.encoding.percent.decode_block_7
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r10, rax
  cmpq [rbp + -96], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_16
  jmp std.encoding.percent.decode_block_22
std.encoding.percent.decode_block_16:
  jmp std.encoding.percent.decode_block_16
  movq $1, rax
  addq $17, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -120]
  jmp std.encoding.percent.decode_block_22
std.encoding.percent.decode_block_22:
  movq [rbp + -120], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_23
  jmp std.encoding.percent.decode_block_172
std.encoding.percent.decode_block_23:
  jmp std.encoding.percent.decode_block_23
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq $1, rax
  addq $25, rax
  movq rax, [rbp + -136]
  movq [rbp + -64], rcx
  movq [rbp + -128], rdx
  movq [rbp + -136], r8
  call substring
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r26, rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_34
  jmp std.encoding.percent.decode_block_38
std.encoding.percent.decode_block_34:
  jmp std.encoding.percent.decode_block_34
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -72], rcx
  movq [rbp + -160], rdx
  call lm_str_concat
  movq rax, [rbp + -168]
  jmp std.encoding.percent.decode_block_167
std.encoding.percent.decode_block_38:
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_str_concat
  movq rax, [rbp + -192]
  movq $r26, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_43
  jmp std.encoding.percent.decode_block_47
std.encoding.percent.decode_block_43:
  jmp std.encoding.percent.decode_block_43
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq [rbp + -168], rcx
  movq [rbp + -208], rdx
  call lm_str_concat
  movq rax, [rbp + -216]
  jmp std.encoding.percent.decode_block_166
std.encoding.percent.decode_block_47:
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_str_concat
  movq rax, [rbp + -240]
  movq $r26, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rbp + -248], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_52
  jmp std.encoding.percent.decode_block_56
std.encoding.percent.decode_block_52:
  jmp std.encoding.percent.decode_block_52
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -216], rcx
  movq [rbp + -256], rdx
  call lm_str_concat
  movq rax, [rbp + -264]
  jmp std.encoding.percent.decode_block_165
std.encoding.percent.decode_block_56:
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_str_concat
  movq rax, [rbp + -288]
  movq $r26, rax
  cmpq [rbp + -288], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_61
  jmp std.encoding.percent.decode_block_65
std.encoding.percent.decode_block_61:
  jmp std.encoding.percent.decode_block_61
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq [rbp + -264], rcx
  movq [rbp + -304], rdx
  call lm_str_concat
  movq rax, [rbp + -312]
  jmp std.encoding.percent.decode_block_164
std.encoding.percent.decode_block_65:
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_str_concat
  movq rax, [rbp + -336]
  movq $r26, rax
  cmpq [rbp + -336], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_70
  jmp std.encoding.percent.decode_block_74
std.encoding.percent.decode_block_70:
  jmp std.encoding.percent.decode_block_70
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -312], rcx
  movq [rbp + -352], rdx
  call lm_str_concat
  movq rax, [rbp + -360]
  jmp std.encoding.percent.decode_block_163
std.encoding.percent.decode_block_74:
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_str_concat
  movq rax, [rbp + -384]
  movq $r26, rax
  cmpq [rbp + -384], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_79
  jmp std.encoding.percent.decode_block_83
std.encoding.percent.decode_block_79:
  jmp std.encoding.percent.decode_block_79
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq [rbp + -360], rcx
  movq [rbp + -400], rdx
  call lm_str_concat
  movq rax, [rbp + -408]
  jmp std.encoding.percent.decode_block_162
std.encoding.percent.decode_block_83:
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_str_concat
  movq rax, [rbp + -432]
  movq $r26, rax
  cmpq [rbp + -432], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -440]
  movq [rbp + -440], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_88
  jmp std.encoding.percent.decode_block_92
std.encoding.percent.decode_block_88:
  jmp std.encoding.percent.decode_block_88
  movq [rel str_const_118], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -408], rcx
  movq [rbp + -448], rdx
  call lm_str_concat
  movq rax, [rbp + -456]
  jmp std.encoding.percent.decode_block_161
std.encoding.percent.decode_block_92:
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -464], rcx
  movq [rbp + -472], rdx
  call lm_str_concat
  movq rax, [rbp + -480]
  movq $r26, rax
  cmpq [rbp + -480], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_97
  jmp std.encoding.percent.decode_block_101
std.encoding.percent.decode_block_97:
  jmp std.encoding.percent.decode_block_97
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -456], rcx
  movq [rbp + -496], rdx
  call lm_str_concat
  movq rax, [rbp + -504]
  jmp std.encoding.percent.decode_block_160
std.encoding.percent.decode_block_101:
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rcx
  movq [rbp + -520], rdx
  call lm_str_concat
  movq rax, [rbp + -528]
  movq $r26, rax
  cmpq [rbp + -528], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_106
  jmp std.encoding.percent.decode_block_110
std.encoding.percent.decode_block_106:
  jmp std.encoding.percent.decode_block_106
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -504], rcx
  movq [rbp + -544], rdx
  call lm_str_concat
  movq rax, [rbp + -552]
  jmp std.encoding.percent.decode_block_159
std.encoding.percent.decode_block_110:
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq $r26, rax
  cmpq [rbp + -560], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -568]
  movq [rbp + -568], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_113
  jmp std.encoding.percent.decode_block_117
std.encoding.percent.decode_block_113:
  jmp std.encoding.percent.decode_block_113
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -552], rcx
  movq [rbp + -576], rdx
  call lm_str_concat
  movq rax, [rbp + -584]
  jmp std.encoding.percent.decode_block_158
std.encoding.percent.decode_block_117:
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq $r26, rax
  cmpq [rbp + -592], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_120
  jmp std.encoding.percent.decode_block_124
std.encoding.percent.decode_block_120:
  jmp std.encoding.percent.decode_block_120
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -584], rcx
  movq [rbp + -608], rdx
  call lm_str_concat
  movq rax, [rbp + -616]
  jmp std.encoding.percent.decode_block_157
std.encoding.percent.decode_block_124:
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -624]
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_str_concat
  movq rax, [rbp + -640]
  movq $r26, rax
  cmpq [rbp + -640], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -648]
  movq [rbp + -648], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_129
  jmp std.encoding.percent.decode_block_133
std.encoding.percent.decode_block_129:
  jmp std.encoding.percent.decode_block_129
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -616], rcx
  movq [rbp + -656], rdx
  call lm_str_concat
  movq rax, [rbp + -664]
  jmp std.encoding.percent.decode_block_156
std.encoding.percent.decode_block_133:
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -680]
  movq [rbp + -672], rcx
  movq [rbp + -680], rdx
  call lm_str_concat
  movq rax, [rbp + -688]
  movq $r26, rax
  cmpq [rbp + -688], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -696]
  movq [rbp + -696], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_138
  jmp std.encoding.percent.decode_block_142
std.encoding.percent.decode_block_138:
  jmp std.encoding.percent.decode_block_138
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -704]
  movq [rbp + -664], rcx
  movq [rbp + -704], rdx
  call lm_str_concat
  movq rax, [rbp + -712]
  jmp std.encoding.percent.decode_block_155
std.encoding.percent.decode_block_142:
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -720]
  movq $r26, rax
  cmpq [rbp + -720], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -728]
  movq [rbp + -728], rax
  testq rax, rax
  jne std.encoding.percent.decode_block_145
  jmp std.encoding.percent.decode_block_149
std.encoding.percent.decode_block_145:
  jmp std.encoding.percent.decode_block_145
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -712], rcx
  movq [rbp + -736], rdx
  call lm_str_concat
  movq rax, [rbp + -744]
  jmp std.encoding.percent.decode_block_154
std.encoding.percent.decode_block_149:
  movq [rel str_const_137], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -744], rcx
  movq [rbp + -752], rdx
  call lm_str_concat
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  movq $r26, rdx
  call lm_str_concat
  movq rax, [rbp + -768]
  jmp std.encoding.percent.decode_block_154
std.encoding.percent.decode_block_154:
  jmp std.encoding.percent.decode_block_155
std.encoding.percent.decode_block_155:
  jmp std.encoding.percent.decode_block_156
std.encoding.percent.decode_block_156:
  jmp std.encoding.percent.decode_block_157
std.encoding.percent.decode_block_157:
  jmp std.encoding.percent.decode_block_158
std.encoding.percent.decode_block_158:
  jmp std.encoding.percent.decode_block_159
std.encoding.percent.decode_block_159:
  jmp std.encoding.percent.decode_block_160
std.encoding.percent.decode_block_160:
  jmp std.encoding.percent.decode_block_161
std.encoding.percent.decode_block_161:
  jmp std.encoding.percent.decode_block_162
std.encoding.percent.decode_block_162:
  jmp std.encoding.percent.decode_block_163
std.encoding.percent.decode_block_163:
  jmp std.encoding.percent.decode_block_164
std.encoding.percent.decode_block_164:
  jmp std.encoding.percent.decode_block_165
std.encoding.percent.decode_block_165:
  jmp std.encoding.percent.decode_block_166
std.encoding.percent.decode_block_166:
  jmp std.encoding.percent.decode_block_167
std.encoding.percent.decode_block_167:
  movq $1, rax
  addq $25, rax
  movq rax, [rbp + -776]
  jmp std.encoding.percent.decode_block_179
std.encoding.percent.decode_block_172:
  movq [rbp + -768], rcx
  movq $r10, rdx
  call lm_str_concat
  movq rax, [rbp + -784]
  movq [rbp + -776], rax
  addq $9, rax
  movq rax, [rbp + -792]
  jmp std.encoding.percent.decode_block_179
std.encoding.percent.decode_block_179:
  jmp std.encoding.percent.decode_block_5
std.encoding.percent.decode_block_180:
  movq [rbp + -784], rax
  jmp std.encoding.percent.decode_epilogue
std.encoding.percent.decode_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.encoding.percent.decode:

.globl std.url.url.build
std.url.url.build:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 184
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
  mov [rbp + -88], r9
std.url.url.build_entry:
std.url.url.build_block_0:
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -120], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -120], rcx
  movq [rbp + -112], rdx
  call std.url.url.URL.init
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -128]
  movq [rbp + -120], rax
  movq [rbp + -128], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -136]
  movq [rbp + -72], rax
  movq [rbp + -136], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -144]
  movq [rbp + -104], rax
  movq [rbp + -144], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -152]
  movq [rbp + -96], rax
  movq [rbp + -152], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -160]
  movq [rbp + -112], rax
  movq [rbp + -160], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -168]
  movq [rbp + -64], rax
  movq [rbp + -168], rdx
  mov [rdx], rax
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -72], rax
  cmpq [rbp + -176], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -120], rax
  addq $0, rax
  movq rax, [rbp + -192]
  movq [rbp + -80], rax
  movq [rbp + -192], rdx
  mov [rdx], rax
  movq [rbp + -120], rax
  jmp std.url.url.build_epilogue
std.url.url.build_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.build:

.globl std.url.query.split_str
std.url.query.split_str:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.query.split_str_entry:
std.url.query.split_str_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.url.query.split_str_block_6
std.url.query.split_str_block_6:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.url.query.split_str_block_9
  jmp std.url.query.split_str_block_32
std.url.query.split_str_block_9:
  jmp std.url.query.split_str_block_9
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -96], r8
  call substring
  movq $r13, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.url.query.split_str_block_15
  jmp std.url.query.split_str_block_19
std.url.query.split_str_block_15:
  jmp std.url.query.split_str_block_15
  movq $r2, rcx
  movq [rbp + -80], rdx
  call lm_list_append
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  jmp std.url.query.split_str_block_27
std.url.query.split_str_block_19:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -120]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -120], r8
  call substring
  movq $r22, rcx
  call lm_to_string
  movq rax, [rbp + -128]
  movq [rbp + -112], rcx
  movq [rbp + -128], rdx
  call lm_str_concat
  movq rax, [rbp + -136]
  jmp std.url.query.split_str_block_27
std.url.query.split_str_block_27:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.url.query.split_str_block_6
std.url.query.split_str_block_32:
  movq $r2, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq $r2, rax
  jmp std.url.query.split_str_epilogue
std.url.query.split_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.split_str:

.globl std.url.url.normalize_path
std.url.url.normalize_path:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 232
  mov [rbp + -64], rcx
std.url.url.normalize_path_entry:
std.url.url.normalize_path_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_142], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  call std.url.url.split_str
  jmp std.url.url.normalize_path_block_8
std.url.url.normalize_path_block_8:
  movq $r5, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r8, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_11
  jmp std.url.url.normalize_path_block_58
std.url.url.normalize_path_block_11:
  jmp std.url.url.normalize_path_block_11
  movq $r5, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r11, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_21
  jmp std.url.url.normalize_path_block_17
std.url.url.normalize_path_block_17:
  jmp std.url.url.normalize_path_block_17
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r11, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  jmp std.url.url.normalize_path_block_21
std.url.url.normalize_path_block_21:
  movq [rbp + -112], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_22
  jmp std.url.url.normalize_path_block_23
std.url.url.normalize_path_block_22:
  jmp std.url.url.normalize_path_block_22
  jmp std.url.url.normalize_path_block_53
std.url.url.normalize_path_block_23:
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r11, rax
  cmpq [rbp + -120], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rbp + -128], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_26
  jmp std.url.url.normalize_path_block_50
std.url.url.normalize_path_block_26:
  jmp std.url.url.normalize_path_block_26
  movq $r1, rcx
  call lm_list_len
  movq $r22, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rbp + -136], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_30
  jmp std.url.url.normalize_path_block_49
std.url.url.normalize_path_block_30:
  jmp std.url.url.normalize_path_block_30
  movq $0, rcx
  call lm_list_new
  jmp std.url.url.normalize_path_block_35
std.url.url.normalize_path_block_35:
  movq $r1, rcx
  call lm_list_len
  movq $r30, rax
  subq $9, rax
  movq rax, $r32
  movq $1, rax
  cmpq $r32, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_40
  jmp std.url.url.normalize_path_block_47
std.url.url.normalize_path_block_40:
  jmp std.url.url.normalize_path_block_40
  movq $r1, rcx
  movq $1, rdx
  call lm_list_get
  movq $r26, rcx
  movq $r35, rdx
  call lm_list_append
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.url.url.normalize_path_block_35
std.url.url.normalize_path_block_47:
  jmp std.url.url.normalize_path_block_49
std.url.url.normalize_path_block_49:
  jmp std.url.url.normalize_path_block_52
std.url.url.normalize_path_block_50:
  movq $r26, rcx
  movq $r11, rdx
  call lm_list_append
  jmp std.url.url.normalize_path_block_52
std.url.url.normalize_path_block_52:
  jmp std.url.url.normalize_path_block_53
std.url.url.normalize_path_block_53:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -160]
  jmp std.url.url.normalize_path_block_8
std.url.url.normalize_path_block_58:
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r48, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_64
  jmp std.url.url.normalize_path_block_71
std.url.url.normalize_path_block_64:
  jmp std.url.url.normalize_path_block_64
  movq [rbp + -64], rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r53, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  jmp std.url.url.normalize_path_block_71
std.url.url.normalize_path_block_71:
  movq [rbp + -192], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_72
  jmp std.url.url.normalize_path_block_75
std.url.url.normalize_path_block_72:
  jmp std.url.url.normalize_path_block_72
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  jmp std.url.url.normalize_path_block_75
std.url.url.normalize_path_block_75:
  jmp std.url.url.normalize_path_block_77
std.url.url.normalize_path_block_77:
  movq $r26, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r59, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rbp + -208], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_80
  jmp std.url.url.normalize_path_block_95
std.url.url.normalize_path_block_80:
  jmp std.url.url.normalize_path_block_80
  movq $1, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -216]
  movq [rbp + -216], rax
  testq rax, rax
  jne std.url.url.normalize_path_block_83
  jmp std.url.url.normalize_path_block_87
std.url.url.normalize_path_block_83:
  jmp std.url.url.normalize_path_block_83
  movq [rel str_const_149], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -200], rcx
  movq [rbp + -224], rdx
  call lm_str_concat
  movq rax, [rbp + -232]
  jmp std.url.url.normalize_path_block_87
std.url.url.normalize_path_block_87:
  movq $r26, rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -232], rcx
  movq $r67, rdx
  call lm_str_concat
  movq rax, [rbp + -240]
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -248]
  jmp std.url.url.normalize_path_block_77
std.url.url.normalize_path_block_95:
  movq [rbp + -240], rax
  jmp std.url.url.normalize_path_epilogue
std.url.url.normalize_path_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.normalize_path:

.globl std.url.query.QueryParams.has
std.url.query.QueryParams.has:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.query.QueryParams.has_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.has_epilogue
std.url.query.QueryParams.has_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.has:

.globl std.url.url.index_of
std.url.url.index_of:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.url.index_of_entry:
std.url.url.index_of_block_0:
  jmp std.url.url.index_of_block_2
std.url.url.index_of_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $r3, rax
  subq $r4, rax
  movq rax, $r5
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.url.url.index_of_block_7
  jmp std.url.url.index_of_block_19
std.url.url.index_of_block_7:
  jmp std.url.url.index_of_block_7
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $1, rax
  addq $r9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r11, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.url.url.index_of_block_13
  jmp std.url.url.index_of_block_14
std.url.url.index_of_block_13:
  jmp std.url.url.index_of_block_13
  movq $1, rax
  jmp std.url.url.index_of_epilogue
std.url.url.index_of_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.url.url.index_of_block_2
std.url.url.index_of_block_19:
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.url.url.index_of_epilogue
std.url.url.index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.index_of:

.globl std.url.url.substring
std.url.url.substring:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
  mov [rbp + -80], r8
std.url.url.substring_entry:
std.url.url.substring_block_0:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -80], rax
  cmpq $r3, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.url.url.substring_block_5
  jmp std.url.url.substring_block_7
std.url.url.substring_block_5:
  jmp std.url.url.substring_block_5
  jmp std.url.url.substring_block_7
std.url.url.substring_block_7:
  movq [rbp + -72], rax
  cmpq $1, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.url.url.substring_block_10
  jmp std.url.url.substring_block_12
std.url.url.substring_block_10:
  jmp std.url.url.substring_block_10
  movq [rel str_const_150], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  jmp std.url.url.substring_epilogue
std.url.url.substring_block_12:
  movq [rbp + -72], rax
  cmpq $r3, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  testq rax, rax
  jne std.url.url.substring_block_14
  jmp std.url.url.substring_block_16
std.url.url.substring_block_14:
  jmp std.url.url.substring_block_14
  movq [rel str_const_151], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  jmp std.url.url.substring_epilogue
std.url.url.substring_block_16:
  movq [rbp + -64], rcx
  movq [rbp + -72], rdx
  movq $r3, r8
  call substring
  movq $r15, rax
  jmp std.url.url.substring_epilogue
std.url.url.substring_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.substring:

.globl std.url.url.__init__
std.url.url.__init__:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 40
std.url.url.__init___entry:
  movq $0, rax
  jmp std.url.url.__init___epilogue
std.url.url.__init___epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.url.__init__:

.globl std.url.query.QueryParams.get_all
std.url.query.QueryParams.get_all:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.query.QueryParams.get_all_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.get_all_epilogue
std.url.query.QueryParams.get_all_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.get_all:

.globl std.url.query.QueryParams.to_string
std.url.query.QueryParams.to_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.query.QueryParams.to_string_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.to_string_epilogue
std.url.query.QueryParams.to_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.to_string:

.globl std.url.query.QueryParams.remove
std.url.query.QueryParams.remove:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.query.QueryParams.remove_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.remove_epilogue
std.url.query.QueryParams.remove_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.remove:

.globl std.url.query.QueryParams.init
std.url.query.QueryParams.init:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.query.QueryParams.init_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.init_epilogue
std.url.query.QueryParams.init_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.init:

.globl std.url.query.parse
std.url.query.parse:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 152
  mov [rbp + -64], rcx
std.url.query.parse_entry:
std.url.query.parse_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -72], rcx
  call std.url.query.QueryParams.init
  movq [rel str_const_152], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.url.query.parse_block_6
  jmp std.url.query.parse_block_7
std.url.query.parse_block_6:
  jmp std.url.query.parse_block_6
  movq [rbp + -72], rax
  jmp std.url.query.parse_epilogue
std.url.query.parse_block_7:
  movq [rel str_const_153], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -64], rcx
  movq [rbp + -96], rdx
  call std.url.query.split_str
  jmp std.url.query.parse_block_12
std.url.query.parse_block_12:
  movq $r8, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r11, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  testq rax, rax
  jne std.url.query.parse_block_15
  jmp std.url.query.parse_block_50
std.url.query.parse_block_15:
  jmp std.url.query.parse_block_15
  movq $r8, rcx
  movq $1, rdx
  call lm_list_get
  movq [rel str_const_154], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r14, rax
  cmpq [rbp + -112], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  testq rax, rax
  jne std.url.query.parse_block_20
  jmp std.url.query.parse_block_45
std.url.query.parse_block_20:
  jmp std.url.query.parse_block_20
  movq [rel str_const_155], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r14, rcx
  movq [rbp + -128], rdx
  call std.url.query.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq $r20, rax
  cmpq [rbp + -136], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.url.query.parse_block_27
  jmp std.url.query.parse_block_40
std.url.query.parse_block_27:
  jmp std.url.query.parse_block_27
  movq $r14, rcx
  movq $1, rdx
  movq $r20, r8
  call substring
  movq $r27, rcx
  call std.encoding.percent.decode
  movq $r20, rax
  addq $9, rax
  movq rax, $r32
  movq $r14, rcx
  call lm_list_len
  movq $r14, rcx
  movq $r32, rdx
  movq $r33, r8
  call substring
  movq $r34, rcx
  call std.encoding.percent.decode
  movq [rbp + -72], rcx
  movq $r28, rdx
  movq $r35, r8
  call std.url.query.QueryParams.add
  jmp std.url.query.parse_block_44
std.url.query.parse_block_40:
  movq $r14, rcx
  call std.encoding.percent.decode
  movq [rel str_const_156], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -72], rcx
  movq $r38, rdx
  movq [rbp + -152], r8
  call std.url.query.QueryParams.add
  jmp std.url.query.parse_block_44
std.url.query.parse_block_44:
  jmp std.url.query.parse_block_45
std.url.query.parse_block_45:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -160]
  jmp std.url.query.parse_block_12
std.url.query.parse_block_50:
  movq [rbp + -72], rax
  jmp std.url.query.parse_epilogue
std.url.query.parse_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.parse:

.globl std.url.builder.URLBuilder.set_password
std.url.builder.URLBuilder.set_password:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_password_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_password_epilogue
std.url.builder.URLBuilder.set_password_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_password:

.globl test_parsing
test_parsing:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 1256
test_parsing_entry:
test_parsing_block_0:
  movq [rel str_const_157], rcx
  call lm_box_string
  movq rax, [rbp + -64]
  movq [rbp + -64], rax
  addq $16, rax
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  mov rax, [rax]
  movq rax, [rbp + -88]
  movq [rbp + -88], rcx
  call lm_print_str
  movq [rel str_const_158], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.url.index.URL
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -120]
  movq [rel str_const_159], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -120], rax
  cmpq [rbp + -128], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -136]
  movq [rel str_const_160], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -136], rcx
  movq [rbp + -144], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -152]
  movq [rbp + -152], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -160]
  movq [rel str_const_161], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -160], rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_162], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  cmpq $641, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_163], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -224]
  movq [rbp + -224], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -232]
  movq [rel str_const_164], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  movq [rel str_const_165], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -248], rcx
  movq [rbp + -256], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -272]
  movq [rel str_const_166], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rax
  cmpq [rbp + -280], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -288]
  movq [rel str_const_167], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq [rbp + -288], rcx
  movq [rbp + -296], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -304]
  movq [rbp + -304], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -312]
  movq [rel str_const_168], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -312], rax
  cmpq [rbp + -320], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -328]
  movq [rel str_const_169], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq [rbp + -328], rcx
  movq [rbp + -336], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -344]
  movq [rbp + -344], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -352]
  movq [rbp + -352], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_170], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rel str_const_171], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -376], rcx
  call std.url.index.URL
  movq $r42, rax
  movq rax, [rbp + -384]
  movq [rbp + -384], rax
  addq $0, rax
  movq rax, [rbp + -392]
  movq [rbp + -392], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -400]
  movq [rel str_const_172], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rax
  cmpq [rbp + -408], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -416]
  movq [rel str_const_173], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq [rbp + -416], rcx
  movq [rbp + -424], rdx
  call lm_assert
  movq [rbp + -384], rax
  addq $0, rax
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -440]
  movq [rel str_const_174], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq [rbp + -440], rax
  cmpq [rbp + -448], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_175], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq [rbp + -384], rax
  addq $0, rax
  movq rax, [rbp + -472]
  movq [rbp + -472], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  cmpq $67545, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -488]
  movq [rel str_const_176], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq [rbp + -488], rcx
  movq [rbp + -496], rdx
  call lm_assert
  movq [rbp + -384], rax
  addq $0, rax
  movq rax, [rbp + -504]
  movq [rbp + -504], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -512]
  movq [rel str_const_177], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -512], rax
  cmpq [rbp + -520], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -528]
  movq [rel str_const_178], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq [rbp + -528], rcx
  movq [rbp + -536], rdx
  call lm_assert
  movq [rel str_const_179], rcx
  call lm_box_string
  movq rax, [rbp + -544]
  movq [rbp + -544], rcx
  call std.url.index.URL
  movq $r66, rax
  movq rax, [rbp + -552]
  movq [rbp + -552], rax
  addq $0, rax
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -568]
  movq [rel str_const_180], rcx
  call lm_box_string
  movq rax, [rbp + -576]
  movq [rbp + -568], rax
  cmpq [rbp + -576], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -584]
  movq [rel str_const_181], rcx
  call lm_box_string
  movq rax, [rbp + -592]
  movq [rbp + -584], rcx
  movq [rbp + -592], rdx
  call lm_assert
  movq [rbp + -552], rax
  addq $0, rax
  movq rax, [rbp + -600]
  movq [rbp + -600], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -608]
  movq [rel str_const_182], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -608], rax
  cmpq [rbp + -616], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -624]
  movq [rel str_const_183], rcx
  call lm_box_string
  movq rax, [rbp + -632]
  movq [rbp + -624], rcx
  movq [rbp + -632], rdx
  call lm_assert
  movq [rbp + -552], rax
  addq $0, rax
  movq rax, [rbp + -640]
  movq [rbp + -640], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -648]
  movq [rel str_const_184], rcx
  call lm_box_string
  movq rax, [rbp + -656]
  movq [rbp + -648], rax
  cmpq [rbp + -656], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -664]
  movq [rel str_const_185], rcx
  call lm_box_string
  movq rax, [rbp + -672]
  movq [rbp + -664], rcx
  movq [rbp + -672], rdx
  call lm_assert
  movq [rbp + -552], rax
  addq $0, rax
  movq rax, [rbp + -680]
  movq [rbp + -680], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -688]
  movq [rel str_const_186], rcx
  call lm_box_string
  movq rax, [rbp + -696]
  movq [rbp + -688], rax
  cmpq [rbp + -696], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -704]
  movq [rel str_const_187], rcx
  call lm_box_string
  movq rax, [rbp + -712]
  movq [rbp + -704], rcx
  movq [rbp + -712], rdx
  call lm_assert
  movq [rbp + -552], rax
  addq $0, rax
  movq rax, [rbp + -720]
  movq [rbp + -720], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -728]
  movq [rel str_const_188], rcx
  call lm_box_string
  movq rax, [rbp + -736]
  movq [rbp + -728], rax
  cmpq [rbp + -736], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -744]
  movq [rel str_const_189], rcx
  call lm_box_string
  movq rax, [rbp + -752]
  movq [rbp + -744], rcx
  movq [rbp + -752], rdx
  call lm_assert
  movq [rel str_const_190], rcx
  call lm_box_string
  movq rax, [rbp + -760]
  movq [rbp + -760], rcx
  call std.url.index.URL
  movq $r95, rax
  movq rax, [rbp + -768]
  movq [rbp + -768], rax
  addq $0, rax
  movq rax, [rbp + -776]
  movq [rbp + -776], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -784]
  movq [rel str_const_191], rcx
  call lm_box_string
  movq rax, [rbp + -792]
  movq [rbp + -784], rax
  cmpq [rbp + -792], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -800]
  movq [rel str_const_192], rcx
  call lm_box_string
  movq rax, [rbp + -808]
  movq [rbp + -800], rcx
  movq [rbp + -808], rdx
  call lm_assert
  movq [rbp + -768], rax
  addq $0, rax
  movq rax, [rbp + -816]
  movq [rbp + -816], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -824]
  movq [rel str_const_193], rcx
  call lm_box_string
  movq rax, [rbp + -832]
  movq [rbp + -824], rax
  cmpq [rbp + -832], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -840]
  movq [rel str_const_194], rcx
  call lm_box_string
  movq rax, [rbp + -848]
  movq [rbp + -840], rcx
  movq [rbp + -848], rdx
  call lm_assert
  movq [rbp + -768], rax
  addq $0, rax
  movq rax, [rbp + -856]
  movq [rbp + -856], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -864]
  movq [rbp + -864], rax
  cmpq $64641, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -872]
  movq [rel str_const_195], rcx
  call lm_box_string
  movq rax, [rbp + -880]
  movq [rbp + -872], rcx
  movq [rbp + -880], rdx
  call lm_assert
  movq [rel str_const_196], rcx
  call lm_box_string
  movq rax, [rbp + -888]
  movq [rbp + -104], rcx
  movq [rbp + -888], rdx
  call std.url.url.URL.resolve
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -896]
  movq [rel str_const_197], rcx
  call lm_box_string
  movq rax, [rbp + -904]
  movq [rbp + -904], rcx
  movq [rbp + -896], rdx
  call lm_rt_str_format
  movq rax, [rbp + -912]
  movq [rbp + -912], rax
  addq $16, rax
  movq rax, [rbp + -920]
  movq [rbp + -920], rax
  movq rax, [rbp + -928]
  movq [rbp + -928], rax
  mov rax, [rax]
  movq rax, [rbp + -936]
  movq [rbp + -936], rcx
  call lm_print_str
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -944]
  movq [rel str_const_198], rcx
  call lm_box_string
  movq rax, [rbp + -952]
  movq [rbp + -952], rcx
  movq [rbp + -944], rdx
  call lm_rt_str_format
  movq rax, [rbp + -960]
  movq [rbp + -960], rax
  addq $16, rax
  movq rax, [rbp + -968]
  movq [rbp + -968], rax
  movq rax, [rbp + -976]
  movq [rbp + -976], rax
  mov rax, [rax]
  movq rax, [rbp + -984]
  movq [rbp + -984], rcx
  call lm_print_str
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -992]
  movq [rel str_const_199], rcx
  call lm_box_string
  movq rax, [rbp + -1000]
  movq [rbp + -1000], rcx
  movq [rbp + -992], rdx
  call lm_rt_str_format
  movq rax, [rbp + -1008]
  movq [rbp + -1008], rax
  addq $16, rax
  movq rax, [rbp + -1016]
  movq [rbp + -1016], rax
  movq rax, [rbp + -1024]
  movq [rbp + -1024], rax
  mov rax, [rax]
  movq rax, [rbp + -1032]
  movq [rbp + -1032], rcx
  call lm_print_str
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -1040]
  movq [rel str_const_200], rcx
  call lm_box_string
  movq rax, [rbp + -1048]
  movq [rbp + -1040], rax
  cmpq [rbp + -1048], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1056]
  movq [rel str_const_201], rcx
  call lm_box_string
  movq rax, [rbp + -1064]
  movq [rbp + -1056], rcx
  movq [rbp + -1064], rdx
  call lm_assert
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -1072]
  movq [rel str_const_202], rcx
  call lm_box_string
  movq rax, [rbp + -1080]
  movq [rbp + -1072], rax
  cmpq [rbp + -1080], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1088]
  movq [rel str_const_203], rcx
  call lm_box_string
  movq rax, [rbp + -1096]
  movq [rbp + -1088], rcx
  movq [rbp + -1096], rdx
  call lm_assert
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -1104]
  movq [rel str_const_204], rcx
  call lm_box_string
  movq rax, [rbp + -1112]
  movq [rbp + -1104], rax
  cmpq [rbp + -1112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1120]
  movq [rel str_const_205], rcx
  call lm_box_string
  movq rax, [rbp + -1128]
  movq [rbp + -1120], rcx
  movq [rbp + -1128], rdx
  call lm_assert
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -1136]
  movq [rel str_const_206], rcx
  call lm_box_string
  movq rax, [rbp + -1144]
  movq [rbp + -1136], rax
  cmpq [rbp + -1144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1152]
  movq [rel str_const_207], rcx
  call lm_box_string
  movq rax, [rbp + -1160]
  movq [rbp + -1152], rcx
  movq [rbp + -1160], rdx
  call lm_assert
  movq $r114, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -1168]
  movq [rel str_const_208], rcx
  call lm_box_string
  movq rax, [rbp + -1176]
  movq [rbp + -1168], rax
  cmpq [rbp + -1176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1184]
  movq [rel str_const_209], rcx
  call lm_box_string
  movq rax, [rbp + -1192]
  movq [rbp + -1184], rcx
  movq [rbp + -1192], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.url.url.URL.origin
  movq [rel str_const_210], rcx
  call lm_box_string
  movq rax, [rbp + -1200]
  movq $r154, rax
  cmpq [rbp + -1200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1208]
  movq [rel str_const_211], rcx
  call lm_box_string
  movq rax, [rbp + -1216]
  movq [rbp + -1208], rcx
  movq [rbp + -1216], rdx
  call lm_assert
  movq [rbp + -384], rcx
  call std.url.url.URL.origin
  movq [rel str_const_212], rcx
  call lm_box_string
  movq rax, [rbp + -1224]
  movq $r159, rax
  cmpq [rbp + -1224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -1232]
  movq [rel str_const_213], rcx
  call lm_box_string
  movq rax, [rbp + -1240]
  movq [rbp + -1232], rcx
  movq [rbp + -1240], rdx
  call lm_assert
  movq [rel str_const_214], rcx
  call lm_box_string
  movq rax, [rbp + -1248]
  movq [rbp + -1248], rax
  addq $16, rax
  movq rax, [rbp + -1256]
  movq [rbp + -1256], rax
  movq rax, [rbp + -1264]
  movq [rbp + -1264], rax
  mov rax, [rax]
  movq rax, [rbp + -1272]
  movq [rbp + -1272], rcx
  call lm_print_str
  movq $9, rax
  jmp test_parsing_epilogue
test_parsing_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_test_parsing:

.globl std.url.builder.URLBuilder.set_host
std.url.builder.URLBuilder.set_host:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_host_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_host_epilogue
std.url.builder.URLBuilder.set_host_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_host:

.globl std.url.builder.URLBuilder.set_port
std.url.builder.URLBuilder.set_port:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_port_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_port_epilogue
std.url.builder.URLBuilder.set_port_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_port:

.globl std.url.query.QueryParams.get
std.url.query.QueryParams.get:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.query.QueryParams.get_entry:
  movq $0, rax
  jmp std.url.query.QueryParams.get_epilogue
std.url.query.QueryParams.get_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.QueryParams.get:

.globl std.url.builder.URLBuilder.set_fragment
std.url.builder.URLBuilder.set_fragment:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_fragment_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_fragment_epilogue
std.url.builder.URLBuilder.set_fragment_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_fragment:

.globl std.url.query.index_of
std.url.query.index_of:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 104
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.query.index_of_entry:
std.url.query.index_of_block_0:
  jmp std.url.query.index_of_block_2
std.url.query.index_of_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $r3, rax
  subq $r4, rax
  movq rax, $r5
  movq $1, rax
  cmpq $r5, rax
  setle al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.url.query.index_of_block_7
  jmp std.url.query.index_of_block_19
std.url.query.index_of_block_7:
  jmp std.url.query.index_of_block_7
  movq [rbp + -72], rcx
  call lm_list_len
  movq [rbp + -72], rcx
  call lm_list_len
  movq $1, rax
  addq $r9, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -88], r8
  call substring
  movq $r11, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.url.query.index_of_block_13
  jmp std.url.query.index_of_block_14
std.url.query.index_of_block_13:
  jmp std.url.query.index_of_block_13
  movq $1, rax
  jmp std.url.query.index_of_epilogue
std.url.query.index_of_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.url.query.index_of_block_2
std.url.query.index_of_block_19:
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.url.query.index_of_epilogue
std.url.query.index_of_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.query.index_of:

.globl std.url.builder.URLBuilder.set_username
std.url.builder.URLBuilder.set_username:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
std.url.builder.URLBuilder.set_username_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.set_username_epilogue
std.url.builder.URLBuilder.set_username_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.set_username:

.globl std.url.builder.URLBuilder.build
std.url.builder.URLBuilder.build:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 56
  mov [rbp + -64], rcx
std.url.builder.URLBuilder.build_entry:
  movq $0, rax
  jmp std.url.builder.URLBuilder.build_epilogue
std.url.builder.URLBuilder.build_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_std.url.builder.URLBuilder.build:

.globl lm_box_string
lm_box_string:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
lm_box_string_entry:
  # Bump Allocation: 24 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 24
  mov [rel heap_ptr], rax
  movq $2, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $8, rax
  movq rax, [rbp + -80]
  movq $3, rax
  movq [rbp + -80], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  addq $16, rax
  movq rax, [rbp + -88]
  movq [rbp + -64], rax
  movq [rbp + -88], rdx
  mov [rdx], rax
  movq [rbp + -72], rax
  jmp lm_box_string_epilogue
lm_box_string_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_box_string:

.globl lm_print_str
lm_print_str:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 136
  mov [rbp + -64], rcx
lm_print_str_entry:
  # Bump Allocation: 8 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -72], rax
  add rax, 8
  mov [rel heap_ptr], rax
  movq $0, rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  jmp lm_print_str_loop
lm_print_str_loop:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -80]
  movq [rbp + -64], rax
  addq [rbp + -80], rax
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  cmpq $0, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -104]
  movq [rbp + -80], rax
  addq $1, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movq [rbp + -72], rdx
  mov [rdx], rax
  movq [rbp + -104], rax
  testq rax, rax
  jne lm_print_str_done
  jmp lm_print_str_loop
lm_print_str_done:
  movq [rbp + -72], rax
  mov rax, [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  subq $1, rax
  movq rax, [rbp + -128]
  subq $32, %rsp
  movq $1, rcx
  movq [rbp + -64], rdx
  movq [rbp + -128], r8
  call _write
  addq $32, %rsp
  subq $32, %rsp
  movq $1, rcx
  movq [rel nl], rdx
  movq $1, r8
  call _write
  addq $32, %rsp
  movq $0, rax
  jmp lm_print_str_epilogue
lm_print_str_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_print_str:

.globl lm_assert
lm_assert:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 72
  mov [rbp + -64], rcx
  mov [rbp + -72], rdx
lm_assert_entry:
  movq [rbp + -64], rax
  testq rax, rax
  jne lm_assert_pass
  jmp lm_assert_fail
lm_assert_fail:
  subq $32, %rsp
  movq $1, rcx
  movq [rel assert_fail], rdx
  movq $17, r8
  call _write
  addq $32, %rsp
  movq $50397203, rax
  movq rax, [rbp + -88]
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_pass:
  movq $0, rax
  jmp lm_assert_epilogue
lm_assert_epilogue:
  lea rsp, [rbp - 56]
  pop r15
  pop r14
  pop r13
  pop r12
  pop rdi
  pop rsi
  pop rbx
  leave
  ret
.Lfunc_end_lm_assert:
