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
  .string " "
.align 8
str_const_1:
  .string "	"
.align 8
str_const_2:
  .string "
"
.align 8
str_const_3:
  .string ""
.align 8
str_const_4:
  .string " "
.align 8
str_const_5:
  .string "	"
.align 8
str_const_6:
  .string "
"
.align 8
str_const_7:
  .string ""
.align 8
str_const_8:
  .string ""
.align 8
str_const_9:
  .string "."
.align 8
str_const_10:
  .string "html"
.align 8
str_const_11:
  .string "htm"
.align 8
str_const_12:
  .string "css"
.align 8
str_const_13:
  .string "js"
.align 8
str_const_14:
  .string "json"
.align 8
str_const_15:
  .string "xml"
.align 8
str_const_16:
  .string "csv"
.align 8
str_const_17:
  .string "txt"
.align 8
str_const_18:
  .string "png"
.align 8
str_const_19:
  .string "jpg"
.align 8
str_const_20:
  .string "jpeg"
.align 8
str_const_21:
  .string "gif"
.align 8
str_const_22:
  .string "webp"
.align 8
str_const_23:
  .string "svg"
.align 8
str_const_24:
  .string "bmp"
.align 8
str_const_25:
  .string "tiff"
.align 8
str_const_26:
  .string "ico"
.align 8
str_const_27:
  .string "mp3"
.align 8
str_const_28:
  .string "wav"
.align 8
str_const_29:
  .string "ogg"
.align 8
str_const_30:
  .string "mp4"
.align 8
str_const_31:
  .string "webm"
.align 8
str_const_32:
  .string "mpeg"
.align 8
str_const_33:
  .string "pdf"
.align 8
str_const_34:
  .string "zip"
.align 8
str_const_35:
  .string "gzip"
.align 8
str_const_36:
  .string "text/html"
.align 8
str_const_37:
  .string "text/html"
.align 8
str_const_38:
  .string "text/css"
.align 8
str_const_39:
  .string "text/javascript"
.align 8
str_const_40:
  .string "application/json"
.align 8
str_const_41:
  .string "text/xml"
.align 8
str_const_42:
  .string "text/csv"
.align 8
str_const_43:
  .string "text/plain"
.align 8
str_const_44:
  .string "image/png"
.align 8
str_const_45:
  .string "image/jpeg"
.align 8
str_const_46:
  .string "image/jpeg"
.align 8
str_const_47:
  .string "image/gif"
.align 8
str_const_48:
  .string "image/webp"
.align 8
str_const_49:
  .string "image/svg+xml"
.align 8
str_const_50:
  .string "image/bmp"
.align 8
str_const_51:
  .string "image/tiff"
.align 8
str_const_52:
  .string "image/x-icon"
.align 8
str_const_53:
  .string "audio/mpeg"
.align 8
str_const_54:
  .string "audio/wav"
.align 8
str_const_55:
  .string "audio/ogg"
.align 8
str_const_56:
  .string "video/mp4"
.align 8
str_const_57:
  .string "video/webm"
.align 8
str_const_58:
  .string "video/mpeg"
.align 8
str_const_59:
  .string "application/pdf"
.align 8
str_const_60:
  .string "application/zip"
.align 8
str_const_61:
  .string "application/gzip"
.align 8
str_const_62:
  .string "application/octet-stream"
.align 8
str_const_63:
  .string ""
.align 8
str_const_64:
  .string "/"
.align 8
str_const_65:
  .string "html"
.align 8
str_const_66:
  .string "css"
.align 8
str_const_67:
  .string "js"
.align 8
str_const_68:
  .string "json"
.align 8
str_const_69:
  .string "xml"
.align 8
str_const_70:
  .string "csv"
.align 8
str_const_71:
  .string "txt"
.align 8
str_const_72:
  .string "png"
.align 8
str_const_73:
  .string "jpg"
.align 8
str_const_74:
  .string "gif"
.align 8
str_const_75:
  .string "webp"
.align 8
str_const_76:
  .string "svg"
.align 8
str_const_77:
  .string "bmp"
.align 8
str_const_78:
  .string "tiff"
.align 8
str_const_79:
  .string "ico"
.align 8
str_const_80:
  .string "mp3"
.align 8
str_const_81:
  .string "wav"
.align 8
str_const_82:
  .string "ogg"
.align 8
str_const_83:
  .string "mp4"
.align 8
str_const_84:
  .string "webm"
.align 8
str_const_85:
  .string "mpeg"
.align 8
str_const_86:
  .string "pdf"
.align 8
str_const_87:
  .string "zip"
.align 8
str_const_88:
  .string "gzip"
.align 8
str_const_89:
  .string "text/html"
.align 8
str_const_90:
  .string "text/css"
.align 8
str_const_91:
  .string "text/javascript"
.align 8
str_const_92:
  .string "application/json"
.align 8
str_const_93:
  .string "text/xml"
.align 8
str_const_94:
  .string "text/csv"
.align 8
str_const_95:
  .string "text/plain"
.align 8
str_const_96:
  .string "image/png"
.align 8
str_const_97:
  .string "image/jpeg"
.align 8
str_const_98:
  .string "image/gif"
.align 8
str_const_99:
  .string "image/webp"
.align 8
str_const_100:
  .string "image/svg+xml"
.align 8
str_const_101:
  .string "image/bmp"
.align 8
str_const_102:
  .string "image/tiff"
.align 8
str_const_103:
  .string "image/x-icon"
.align 8
str_const_104:
  .string "audio/mpeg"
.align 8
str_const_105:
  .string "audio/wav"
.align 8
str_const_106:
  .string "audio/ogg"
.align 8
str_const_107:
  .string "video/mp4"
.align 8
str_const_108:
  .string "video/webm"
.align 8
str_const_109:
  .string "video/mpeg"
.align 8
str_const_110:
  .string "application/pdf"
.align 8
str_const_111:
  .string "application/zip"
.align 8
str_const_112:
  .string "application/gzip"
.align 8
str_const_113:
  .string "."
.align 8
str_const_114:
  .string ""
.align 8
str_const_115:
  .string ""
.align 8
str_const_116:
  .string "ABCDEFGHIJKLMNOPQRSTUVWXYZ"
.align 8
str_const_117:
  .string "abcdefghijklmnopqrstuvwxyz"
.align 8
str_const_118:
  .string "Running extension mapping tests..."
.align 8
str_const_119:
  .string "html"
.align 8
str_const_120:
  .string "text/html"
.align 8
str_const_121:
  .string "html failed"
.align 8
str_const_122:
  .string ".css"
.align 8
str_const_123:
  .string "text/css"
.align 8
str_const_124:
  .string ".css failed"
.align 8
str_const_125:
  .string "json"
.align 8
str_const_126:
  .string "application/json"
.align 8
str_const_127:
  .string "json failed"
.align 8
str_const_128:
  .string "JS"
.align 8
str_const_129:
  .string "text/javascript"
.align 8
str_const_130:
  .string "JS case failed"
.align 8
str_const_131:
  .string "unknown"
.align 8
str_const_132:
  .string "application/octet-stream"
.align 8
str_const_133:
  .string "unknown failed"
.align 8
str_const_134:
  .string "text/html"
.align 8
str_const_135:
  .string ".html"
.align 8
str_const_136:
  .string "text/html failed"
.align 8
str_const_137:
  .string "application/json"
.align 8
str_const_138:
  .string ".json"
.align 8
str_const_139:
  .string "application/json failed"
.align 8
str_const_140:
  .string "image/png"
.align 8
str_const_141:
  .string ".png"
.align 8
str_const_142:
  .string "image/png failed"
.align 8
str_const_143:
  .string "text/plain"
.align 8
str_const_144:
  .string ".txt"
.align 8
str_const_145:
  .string "text/plain failed"
.align 8
str_const_146:
  .string "application/unknown"
.align 8
str_const_147:
  .string ""
.align 8
str_const_148:
  .string "unknown mime failed"
.align 8
str_const_149:
  .string "Extension mapping tests passed!"
.align 8
str_const_150:
  .string "Running MIME classification tests..."
.align 8
str_const_151:
  .string "text/plain"
.align 8
str_const_152:
  .string "image/png"
.align 8
str_const_153:
  .string "audio/mpeg"
.align 8
str_const_154:
  .string "video/mp4"
.align 8
str_const_155:
  .string "application/json"
.align 8
str_const_156:
  .string "text should be text"
.align 8
str_const_157:
  .string "text should not be image"
.align 8
str_const_158:
  .string "image should be image"
.align 8
str_const_159:
  .string "audio should be audio"
.align 8
str_const_160:
  .string "video should be video"
.align 8
str_const_161:
  .string "app should be application"
.align 8
str_const_162:
  .string "Classification tests passed!"
.align 8
str_const_163:
  .string "Running MIME parsing tests..."
.align 8
str_const_164:
  .string "text/html"
.align 8
str_const_165:
  .string "m1 should be valid"
.align 8
str_const_166:
  .string "text"
.align 8
str_const_167:
  .string "m1.main_type should be text"
.align 8
str_const_168:
  .string "html"
.align 8
str_const_169:
  .string "m1.subtype should be html"
.align 8
str_const_170:
  .string "text/html"
.align 8
str_const_171:
  .string "m1.to_string() failed"
.align 8
str_const_172:
  .string "  TEXT/Html; charset=utf-8; Boundary=some-boundary  "
.align 8
str_const_173:
  .string "m2 should be valid"
.align 8
str_const_174:
  .string "text"
.align 8
str_const_175:
  .string "m2.main_type should be text"
.align 8
str_const_176:
  .string "html"
.align 8
str_const_177:
  .string "m2.subtype should be html"
.align 8
str_const_178:
  .string "charset"
.align 8
str_const_179:
  .string "utf-8"
.align 8
str_const_180:
  .string "charset failed"
.align 8
str_const_181:
  .string "boundary"
.align 8
str_const_182:
  .string "some-boundary"
.align 8
str_const_183:
  .string "boundary failed"
.align 8
str_const_184:
  .string "invalid-mime-no-slash"
.align 8
str_const_185:
  .string "m3 should be invalid"
.align 8
str_const_186:
  .string "text/"
.align 8
str_const_187:
  .string "m4 should be invalid"
.align 8
str_const_188:
  .string "/html"
.align 8
str_const_189:
  .string "m5 should be invalid"
.align 8
str_const_190:
  .string "Parsing tests passed!"
.align 8
str_const_191:
  .string "Running MIME parameters tests..."
.align 8
str_const_192:
  .string "charset"
.align 8
str_const_193:
  .string "utf-8"
.align 8
str_const_194:
  .string "boundary"
.align 8
str_const_195:
  .string "xyz"
.align 8
str_const_196:
  .string "charset"
.align 8
str_const_197:
  .string "utf-8"
.align 8
str_const_198:
  .string "get charset failed"
.align 8
str_const_199:
  .string "boundary"
.align 8
str_const_200:
  .string "xyz"
.align 8
str_const_201:
  .string "get boundary failed"
.align 8
str_const_202:
  .string "charset"
.align 8
str_const_203:
  .string "has charset failed"
.align 8
str_const_204:
  .string "none"
.align 8
str_const_205:
  .string "has none failed"
.align 8
str_const_206:
  .string "boundary"
.align 8
str_const_207:
  .string "boundary"
.align 8
str_const_208:
  .string "remove failed"
.align 8
str_const_209:
  .string "Parameters tests passed!"
.align 8
str_const_210:
  .string "=== MIME Module Test Suite ==="
.align 8
str_const_211:
  .string "Parsing tests failed"
.align 8
str_const_212:
  .string "Classification tests failed"
.align 8
str_const_213:
  .string "Parameters tests failed"
.align 8
str_const_214:
  .string "Extension mapping tests failed"
.align 8
str_const_215:
  .string "All MIME tests completed successfully."
.align 8
str_const_216:
  .string ""
.align 8
str_const_217:
  .string ""
.align 8
str_const_218:
  .string ""
.align 8
str_const_219:
  .string ""
.align 8
str_const_220:
  .string ""
.align 8
str_const_221:
  .string ";"
.align 8
str_const_222:
  .string "/"
.align 8
str_const_223:
  .string ""
.align 8
str_const_224:
  .string ""
.align 8
str_const_225:
  .string ""
.align 8
str_const_226:
  .string ""
.align 8
str_const_227:
  .string ""
.align 8
str_const_228:
  .string ""
.align 8
str_const_229:
  .string ""
.align 8
str_const_230:
  .string "="
.align 8
str_const_231:
  .string ""
.align 8
str_const_232:
  .string """
.align 8
str_const_233:
  .string """
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
  sub rsp, 168
main_entry:
main_block_0:
  call std.mime.index.__init__
  call std.mime.types.__init__
  call main
  movq $0, rax
  jmp main_epilogue
main_entry:
main_block_0:
  movq [rel str_const_210], rcx
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
  movq [rel str_const_211], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_assert
  call test_classification
  movq $r7, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_212], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  call test_parameters
  movq $r12, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_213], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  call test_extension_mapping
  movq $r17, rax
  cmpq $9, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_214], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_215], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rax
  addq $16, rax
  movq rax, [rbp + -168]
  movq [rbp + -168], rax
  movq rax, [rbp + -176]
  movq [rbp + -176], rax
  mov rax, [rax]
  movq rax, [rbp + -184]
  movq [rbp + -184], rcx
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

.globl std.mime.index.MIMEType
std.mime.index.MIMEType:
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
std.mime.index.MIMEType_entry:
std.mime.index.MIMEType_block_0:
  movq [rbp + -80], rax
  movq rax, [rbp + -96]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rcx
  movq [rbp + -64], rdx
  movq [rbp + -72], r8
  movq [rbp + -96], r9
  call std.mime.types.MIMEType.init
  movq [rbp + -104], rax
  jmp std.mime.index.MIMEType_epilogue
std.mime.index.MIMEType_epilogue:
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
.Lfunc_end_std.mime.index.MIMEType:

.globl std.mime.types.__init__
std.mime.types.__init__:
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
std.mime.types.__init___entry:
  movq $0, rax
  jmp std.mime.types.__init___epilogue
std.mime.types.__init___epilogue:
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
.Lfunc_end_std.mime.types.__init__:

.globl std.mime.types.trim
std.mime.types.trim:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 248
  mov [rbp + -64], rcx
std.mime.types.trim_entry:
std.mime.types.trim_block_0:
  jmp std.mime.types.trim_block_2
std.mime.types.trim_block_2:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r3, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.mime.types.trim_block_6
  jmp std.mime.types.trim_block_44
std.mime.types.trim_block_6:
  jmp std.mime.types.trim_block_6
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -80]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -80], r8
  call substring
  movq [rel str_const_0], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq $r11, rax
  cmpq [rbp + -88], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.mime.types.trim_block_22
  jmp std.mime.types.trim_block_14
std.mime.types.trim_block_14:
  jmp std.mime.types.trim_block_14
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rel str_const_1], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r17, rax
  cmpq [rbp + -112], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -120]
  jmp std.mime.types.trim_block_22
std.mime.types.trim_block_22:
  movq [rbp + -120], rax
  testq rax, rax
  jne std.mime.types.trim_block_32
  jmp std.mime.types.trim_block_24
std.mime.types.trim_block_24:
  jmp std.mime.types.trim_block_24
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -128]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -128], r8
  call substring
  movq [rel str_const_2], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r23, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  jmp std.mime.types.trim_block_32
std.mime.types.trim_block_32:
  movq [rbp + -144], rax
  testq rax, rax
  jne std.mime.types.trim_block_42
  jmp std.mime.types.trim_block_34
std.mime.types.trim_block_34:
  jmp std.mime.types.trim_block_34
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -152], r8
  call substring
  movq [rel str_const_3], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r29, rax
  cmpq [rbp + -160], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  jmp std.mime.types.trim_block_42
std.mime.types.trim_block_42:
  jmp std.mime.types.trim_block_44
std.mime.types.trim_block_44:
  movq [rbp + -168], rax
  testq rax, rax
  jne std.mime.types.trim_block_45
  jmp std.mime.types.trim_block_50
std.mime.types.trim_block_45:
  jmp std.mime.types.trim_block_45
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -176]
  jmp std.mime.types.trim_block_2
std.mime.types.trim_block_50:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $r36, rax
  subq $9, rax
  movq rax, $r38
  jmp std.mime.types.trim_block_55
std.mime.types.trim_block_55:
  movq $r38, rax
  cmpq [rbp + -176], rax
  setge al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  testq rax, rax
  jne std.mime.types.trim_block_58
  jmp std.mime.types.trim_block_96
std.mime.types.trim_block_58:
  jmp std.mime.types.trim_block_58
  movq $r38, rax
  addq $9, rax
  movq rax, $r47
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r47, r8
  call substring
  movq [rel str_const_4], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r48, rax
  cmpq [rbp + -192], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -200]
  movq [rbp + -200], rax
  testq rax, rax
  jne std.mime.types.trim_block_74
  jmp std.mime.types.trim_block_66
std.mime.types.trim_block_66:
  jmp std.mime.types.trim_block_66
  movq $r38, rax
  addq $9, rax
  movq rax, $r53
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r53, r8
  call substring
  movq [rel str_const_5], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r54, rax
  cmpq [rbp + -208], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -216]
  jmp std.mime.types.trim_block_74
std.mime.types.trim_block_74:
  movq [rbp + -216], rax
  testq rax, rax
  jne std.mime.types.trim_block_84
  jmp std.mime.types.trim_block_76
std.mime.types.trim_block_76:
  jmp std.mime.types.trim_block_76
  movq $r38, rax
  addq $9, rax
  movq rax, $r59
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r59, r8
  call substring
  movq [rel str_const_6], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r60, rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  jmp std.mime.types.trim_block_84
std.mime.types.trim_block_84:
  movq [rbp + -232], rax
  testq rax, rax
  jne std.mime.types.trim_block_94
  jmp std.mime.types.trim_block_86
std.mime.types.trim_block_86:
  jmp std.mime.types.trim_block_86
  movq $r38, rax
  addq $9, rax
  movq rax, $r65
  movq [rbp + -64], rcx
  movq $r38, rdx
  movq $r65, r8
  call substring
  movq [rel str_const_7], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r66, rax
  cmpq [rbp + -240], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -248]
  jmp std.mime.types.trim_block_94
std.mime.types.trim_block_94:
  jmp std.mime.types.trim_block_96
std.mime.types.trim_block_96:
  movq [rbp + -248], rax
  testq rax, rax
  jne std.mime.types.trim_block_97
  jmp std.mime.types.trim_block_101
std.mime.types.trim_block_97:
  jmp std.mime.types.trim_block_97
  movq $r38, rax
  subq $9, rax
  movq rax, $r71
  jmp std.mime.types.trim_block_55
std.mime.types.trim_block_101:
  movq [rbp + -176], rax
  cmpq $r71, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  testq rax, rax
  jne std.mime.types.trim_block_103
  jmp std.mime.types.trim_block_105
std.mime.types.trim_block_103:
  jmp std.mime.types.trim_block_103
  movq [rel str_const_8], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  jmp std.mime.types.trim_epilogue
std.mime.types.trim_block_105:
  movq $r71, rax
  addq $9, rax
  movq rax, $r77
  movq [rbp + -64], rcx
  movq [rbp + -176], rdx
  movq $r77, r8
  call substring
  movq $r78, rax
  jmp std.mime.types.trim_epilogue
std.mime.types.trim_epilogue:
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
.Lfunc_end_std.mime.types.trim:

.globl std.mime.types.MIMEType.is_application
std.mime.types.MIMEType.is_application:
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
std.mime.types.MIMEType.is_application_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.is_application_epilogue
std.mime.types.MIMEType.is_application_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_application:

.globl std.mime.types.MIMEType.is_video
std.mime.types.MIMEType.is_video:
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
std.mime.types.MIMEType.is_video_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.is_video_epilogue
std.mime.types.MIMEType.is_video_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_video:

.globl std.mime.types.MIMEType.is_image
std.mime.types.MIMEType.is_image:
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
std.mime.types.MIMEType.is_image_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.is_image_epilogue
std.mime.types.MIMEType.is_image_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_image:

.globl std.mime.types.MIMEType.is_text
std.mime.types.MIMEType.is_text:
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
std.mime.types.MIMEType.is_text_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.is_text_epilogue
std.mime.types.MIMEType.is_text_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_text:

.globl std.mime.index.extension_to_mime
std.mime.index.extension_to_mime:
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
std.mime.index.extension_to_mime_entry:
std.mime.index.extension_to_mime_block_0:
  movq [rbp + -64], rcx
  call std.mime.types.extension_to_mime
  movq $r1, rax
  jmp std.mime.index.extension_to_mime_epilogue
std.mime.index.extension_to_mime_epilogue:
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
.Lfunc_end_std.mime.index.extension_to_mime:

.globl std.mime.types.extension_to_mime
std.mime.types.extension_to_mime:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 520
  mov [rbp + -64], rcx
std.mime.types.extension_to_mime_entry:
std.mime.types.extension_to_mime_block_0:
  movq [rbp + -64], rcx
  call std.mime.types.trim
  movq $r1, rcx
  call std.mime.types.to_lower
  movq $r2, rcx
  call lm_list_len
  movq $r5, rax
  cmpq $1, rax
  setg al
  movzx eax, al
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  testq rax, rax
  jne std.mime.types.extension_to_mime_block_8
  jmp std.mime.types.extension_to_mime_block_15
std.mime.types.extension_to_mime_block_8:
  jmp std.mime.types.extension_to_mime_block_8
  movq $r2, rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_9], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq $r10, rax
  cmpq [rbp + -80], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -88]
  jmp std.mime.types.extension_to_mime_block_15
std.mime.types.extension_to_mime_block_15:
  movq [rbp + -88], rax
  testq rax, rax
  jne std.mime.types.extension_to_mime_block_16
  jmp std.mime.types.extension_to_mime_block_21
std.mime.types.extension_to_mime_block_16:
  jmp std.mime.types.extension_to_mime_block_16
  movq $r2, rcx
  call lm_list_len
  movq $r2, rcx
  movq $9, rdx
  movq $r15, r8
  call substring
  jmp std.mime.types.extension_to_mime_block_21
std.mime.types.extension_to_mime_block_21:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_10], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq $r17, rcx
  movq [rbp + -96], rdx
  call lm_list_append
  movq [rel str_const_11], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r17, rcx
  movq [rbp + -104], rdx
  call lm_list_append
  movq [rel str_const_12], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq $r17, rcx
  movq [rbp + -112], rdx
  call lm_list_append
  movq [rel str_const_13], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r17, rcx
  movq [rbp + -120], rdx
  call lm_list_append
  movq [rel str_const_14], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r17, rcx
  movq [rbp + -128], rdx
  call lm_list_append
  movq [rel str_const_15], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r17, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq [rel str_const_16], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r17, rcx
  movq [rbp + -144], rdx
  call lm_list_append
  movq [rel str_const_17], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r17, rcx
  movq [rbp + -152], rdx
  call lm_list_append
  movq [rel str_const_18], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r17, rcx
  movq [rbp + -160], rdx
  call lm_list_append
  movq [rel str_const_19], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r17, rcx
  movq [rbp + -168], rdx
  call lm_list_append
  movq [rel str_const_20], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r17, rcx
  movq [rbp + -176], rdx
  call lm_list_append
  movq [rel str_const_21], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r17, rcx
  movq [rbp + -184], rdx
  call lm_list_append
  movq [rel str_const_22], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r17, rcx
  movq [rbp + -192], rdx
  call lm_list_append
  movq [rel str_const_23], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r17, rcx
  movq [rbp + -200], rdx
  call lm_list_append
  movq [rel str_const_24], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r17, rcx
  movq [rbp + -208], rdx
  call lm_list_append
  movq [rel str_const_25], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r17, rcx
  movq [rbp + -216], rdx
  call lm_list_append
  movq [rel str_const_26], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r17, rcx
  movq [rbp + -224], rdx
  call lm_list_append
  movq [rel str_const_27], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r17, rcx
  movq [rbp + -232], rdx
  call lm_list_append
  movq [rel str_const_28], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r17, rcx
  movq [rbp + -240], rdx
  call lm_list_append
  movq [rel str_const_29], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $r17, rcx
  movq [rbp + -248], rdx
  call lm_list_append
  movq [rel str_const_30], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r17, rcx
  movq [rbp + -256], rdx
  call lm_list_append
  movq [rel str_const_31], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r17, rcx
  movq [rbp + -264], rdx
  call lm_list_append
  movq [rel str_const_32], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $r17, rcx
  movq [rbp + -272], rdx
  call lm_list_append
  movq [rel str_const_33], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq $r17, rcx
  movq [rbp + -280], rdx
  call lm_list_append
  movq [rel str_const_34], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq $r17, rcx
  movq [rbp + -288], rdx
  call lm_list_append
  movq [rel str_const_35], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $r17, rcx
  movq [rbp + -296], rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_36], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq $r72, rcx
  movq [rbp + -304], rdx
  call lm_list_append
  movq [rel str_const_37], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq $r72, rcx
  movq [rbp + -312], rdx
  call lm_list_append
  movq [rel str_const_38], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r72, rcx
  movq [rbp + -320], rdx
  call lm_list_append
  movq [rel str_const_39], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq $r72, rcx
  movq [rbp + -328], rdx
  call lm_list_append
  movq [rel str_const_40], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq $r72, rcx
  movq [rbp + -336], rdx
  call lm_list_append
  movq [rel str_const_41], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq $r72, rcx
  movq [rbp + -344], rdx
  call lm_list_append
  movq [rel str_const_42], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r72, rcx
  movq [rbp + -352], rdx
  call lm_list_append
  movq [rel str_const_43], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq $r72, rcx
  movq [rbp + -360], rdx
  call lm_list_append
  movq [rel str_const_44], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $r72, rcx
  movq [rbp + -368], rdx
  call lm_list_append
  movq [rel str_const_45], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq $r72, rcx
  movq [rbp + -376], rdx
  call lm_list_append
  movq [rel str_const_46], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq $r72, rcx
  movq [rbp + -384], rdx
  call lm_list_append
  movq [rel str_const_47], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r72, rcx
  movq [rbp + -392], rdx
  call lm_list_append
  movq [rel str_const_48], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq $r72, rcx
  movq [rbp + -400], rdx
  call lm_list_append
  movq [rel str_const_49], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq $r72, rcx
  movq [rbp + -408], rdx
  call lm_list_append
  movq [rel str_const_50], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $r72, rcx
  movq [rbp + -416], rdx
  call lm_list_append
  movq [rel str_const_51], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq $r72, rcx
  movq [rbp + -424], rdx
  call lm_list_append
  movq [rel str_const_52], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq $r72, rcx
  movq [rbp + -432], rdx
  call lm_list_append
  movq [rel str_const_53], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq $r72, rcx
  movq [rbp + -440], rdx
  call lm_list_append
  movq [rel str_const_54], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r72, rcx
  movq [rbp + -448], rdx
  call lm_list_append
  movq [rel str_const_55], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq $r72, rcx
  movq [rbp + -456], rdx
  call lm_list_append
  movq [rel str_const_56], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq $r72, rcx
  movq [rbp + -464], rdx
  call lm_list_append
  movq [rel str_const_57], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq $r72, rcx
  movq [rbp + -472], rdx
  call lm_list_append
  movq [rel str_const_58], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq $r72, rcx
  movq [rbp + -480], rdx
  call lm_list_append
  movq [rel str_const_59], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq $r72, rcx
  movq [rbp + -488], rdx
  call lm_list_append
  movq [rel str_const_60], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq $r72, rcx
  movq [rbp + -496], rdx
  call lm_list_append
  movq [rel str_const_61], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq $r72, rcx
  movq [rbp + -504], rdx
  call lm_list_append
  jmp std.mime.types.extension_to_mime_block_133
std.mime.types.extension_to_mime_block_133:
  movq $r17, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r128, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -512]
  movq [rbp + -512], rax
  testq rax, rax
  jne std.mime.types.extension_to_mime_block_136
  jmp std.mime.types.extension_to_mime_block_146
std.mime.types.extension_to_mime_block_136:
  jmp std.mime.types.extension_to_mime_block_136
  movq $r17, rcx
  movq $1, rdx
  call lm_list_get
  movq $r131, rax
  cmpq $r16, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  testq rax, rax
  jne std.mime.types.extension_to_mime_block_139
  jmp std.mime.types.extension_to_mime_block_141
std.mime.types.extension_to_mime_block_139:
  jmp std.mime.types.extension_to_mime_block_139
  movq $r72, rcx
  movq $1, rdx
  call lm_list_get
  movq $r134, rax
  jmp std.mime.types.extension_to_mime_epilogue
std.mime.types.extension_to_mime_block_141:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -528]
  jmp std.mime.types.extension_to_mime_block_133
std.mime.types.extension_to_mime_block_146:
  movq [rel str_const_62], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  jmp std.mime.types.extension_to_mime_epilogue
std.mime.types.extension_to_mime_epilogue:
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
.Lfunc_end_std.mime.types.extension_to_mime:

.globl std.mime.types.MIMEParams.add
std.mime.types.MIMEParams.add:
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
std.mime.types.MIMEParams.add_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.add_epilogue
std.mime.types.MIMEParams.add_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.add:

.globl std.mime.types.index_of
std.mime.types.index_of:
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
std.mime.types.index_of_entry:
std.mime.types.index_of_block_0:
  jmp std.mime.types.index_of_block_2
std.mime.types.index_of_block_2:
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
  jne std.mime.types.index_of_block_7
  jmp std.mime.types.index_of_block_19
std.mime.types.index_of_block_7:
  jmp std.mime.types.index_of_block_7
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
  jne std.mime.types.index_of_block_13
  jmp std.mime.types.index_of_block_14
std.mime.types.index_of_block_13:
  jmp std.mime.types.index_of_block_13
  movq $1, rax
  jmp std.mime.types.index_of_epilogue
std.mime.types.index_of_block_14:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  jmp std.mime.types.index_of_block_2
std.mime.types.index_of_block_19:
  movq $9, rax
  negq rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  jmp std.mime.types.index_of_epilogue
std.mime.types.index_of_epilogue:
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
.Lfunc_end_std.mime.types.index_of:

.globl std.mime.types.mime_to_extension
std.mime.types.mime_to_extension:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 552
  mov [rbp + -64], rcx
std.mime.types.mime_to_extension_entry:
std.mime.types.mime_to_extension_block_0:
  movq [rbp + -64], rcx
  call std.mime.types.parse
  movq $r1, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -72]
  movq [rbp + -72], rax
  cmpq $18, rax
  setne al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.mime.types.mime_to_extension_block_6
  jmp std.mime.types.mime_to_extension_block_8
std.mime.types.mime_to_extension_block_6:
  jmp std.mime.types.mime_to_extension_block_6
  movq [rel str_const_63], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  jmp std.mime.types.mime_to_extension_epilogue
std.mime.types.mime_to_extension_block_8:
  movq $r1, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -96]
  movq [rel str_const_64], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  call lm_str_concat
  movq rax, [rbp + -112]
  movq $r1, rax
  addq $0, rax
  movq rax, $
  movq $, rax
  mov eax, dword ptr [rax]
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_str_concat
  movq rax, [rbp + -128]
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_65], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r14, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq [rel str_const_66], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r14, rcx
  movq [rbp + -144], rdx
  call lm_list_append
  movq [rel str_const_67], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq $r14, rcx
  movq [rbp + -152], rdx
  call lm_list_append
  movq [rel str_const_68], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq $r14, rcx
  movq [rbp + -160], rdx
  call lm_list_append
  movq [rel str_const_69], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r14, rcx
  movq [rbp + -168], rdx
  call lm_list_append
  movq [rel str_const_70], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r14, rcx
  movq [rbp + -176], rdx
  call lm_list_append
  movq [rel str_const_71], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r14, rcx
  movq [rbp + -184], rdx
  call lm_list_append
  movq [rel str_const_72], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq $r14, rcx
  movq [rbp + -192], rdx
  call lm_list_append
  movq [rel str_const_73], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r14, rcx
  movq [rbp + -200], rdx
  call lm_list_append
  movq [rel str_const_74], rcx
  call lm_box_string
  movq rax, [rbp + -208]
  movq $r14, rcx
  movq [rbp + -208], rdx
  call lm_list_append
  movq [rel str_const_75], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq $r14, rcx
  movq [rbp + -216], rdx
  call lm_list_append
  movq [rel str_const_76], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r14, rcx
  movq [rbp + -224], rdx
  call lm_list_append
  movq [rel str_const_77], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r14, rcx
  movq [rbp + -232], rdx
  call lm_list_append
  movq [rel str_const_78], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq $r14, rcx
  movq [rbp + -240], rdx
  call lm_list_append
  movq [rel str_const_79], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq $r14, rcx
  movq [rbp + -248], rdx
  call lm_list_append
  movq [rel str_const_80], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq $r14, rcx
  movq [rbp + -256], rdx
  call lm_list_append
  movq [rel str_const_81], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r14, rcx
  movq [rbp + -264], rdx
  call lm_list_append
  movq [rel str_const_82], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq $r14, rcx
  movq [rbp + -272], rdx
  call lm_list_append
  movq [rel str_const_83], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq $r14, rcx
  movq [rbp + -280], rdx
  call lm_list_append
  movq [rel str_const_84], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq $r14, rcx
  movq [rbp + -288], rdx
  call lm_list_append
  movq [rel str_const_85], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $r14, rcx
  movq [rbp + -296], rdx
  call lm_list_append
  movq [rel str_const_86], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq $r14, rcx
  movq [rbp + -304], rdx
  call lm_list_append
  movq [rel str_const_87], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq $r14, rcx
  movq [rbp + -312], rdx
  call lm_list_append
  movq [rel str_const_88], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq $r14, rcx
  movq [rbp + -320], rdx
  call lm_list_append
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_89], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq $r65, rcx
  movq [rbp + -328], rdx
  call lm_list_append
  movq [rel str_const_90], rcx
  call lm_box_string
  movq rax, [rbp + -336]
  movq $r65, rcx
  movq [rbp + -336], rdx
  call lm_list_append
  movq [rel str_const_91], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq $r65, rcx
  movq [rbp + -344], rdx
  call lm_list_append
  movq [rel str_const_92], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq $r65, rcx
  movq [rbp + -352], rdx
  call lm_list_append
  movq [rel str_const_93], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq $r65, rcx
  movq [rbp + -360], rdx
  call lm_list_append
  movq [rel str_const_94], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq $r65, rcx
  movq [rbp + -368], rdx
  call lm_list_append
  movq [rel str_const_95], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq $r65, rcx
  movq [rbp + -376], rdx
  call lm_list_append
  movq [rel str_const_96], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq $r65, rcx
  movq [rbp + -384], rdx
  call lm_list_append
  movq [rel str_const_97], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r65, rcx
  movq [rbp + -392], rdx
  call lm_list_append
  movq [rel str_const_98], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq $r65, rcx
  movq [rbp + -400], rdx
  call lm_list_append
  movq [rel str_const_99], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq $r65, rcx
  movq [rbp + -408], rdx
  call lm_list_append
  movq [rel str_const_100], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq $r65, rcx
  movq [rbp + -416], rdx
  call lm_list_append
  movq [rel str_const_101], rcx
  call lm_box_string
  movq rax, [rbp + -424]
  movq $r65, rcx
  movq [rbp + -424], rdx
  call lm_list_append
  movq [rel str_const_102], rcx
  call lm_box_string
  movq rax, [rbp + -432]
  movq $r65, rcx
  movq [rbp + -432], rdx
  call lm_list_append
  movq [rel str_const_103], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq $r65, rcx
  movq [rbp + -440], rdx
  call lm_list_append
  movq [rel str_const_104], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r65, rcx
  movq [rbp + -448], rdx
  call lm_list_append
  movq [rel str_const_105], rcx
  call lm_box_string
  movq rax, [rbp + -456]
  movq $r65, rcx
  movq [rbp + -456], rdx
  call lm_list_append
  movq [rel str_const_106], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq $r65, rcx
  movq [rbp + -464], rdx
  call lm_list_append
  movq [rel str_const_107], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq $r65, rcx
  movq [rbp + -472], rdx
  call lm_list_append
  movq [rel str_const_108], rcx
  call lm_box_string
  movq rax, [rbp + -480]
  movq $r65, rcx
  movq [rbp + -480], rdx
  call lm_list_append
  movq [rel str_const_109], rcx
  call lm_box_string
  movq rax, [rbp + -488]
  movq $r65, rcx
  movq [rbp + -488], rdx
  call lm_list_append
  movq [rel str_const_110], rcx
  call lm_box_string
  movq rax, [rbp + -496]
  movq $r65, rcx
  movq [rbp + -496], rdx
  call lm_list_append
  movq [rel str_const_111], rcx
  call lm_box_string
  movq rax, [rbp + -504]
  movq $r65, rcx
  movq [rbp + -504], rdx
  call lm_list_append
  movq [rel str_const_112], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq $r65, rcx
  movq [rbp + -512], rdx
  call lm_list_append
  jmp std.mime.types.mime_to_extension_block_118
std.mime.types.mime_to_extension_block_118:
  movq $r65, rcx
  call lm_list_len
  movq $1, rax
  cmpq $r117, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -520]
  movq [rbp + -520], rax
  testq rax, rax
  jne std.mime.types.mime_to_extension_block_121
  jmp std.mime.types.mime_to_extension_block_133
std.mime.types.mime_to_extension_block_121:
  jmp std.mime.types.mime_to_extension_block_121
  movq $r65, rcx
  movq $1, rdx
  call lm_list_get
  movq $r120, rax
  cmpq [rbp + -128], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  testq rax, rax
  jne std.mime.types.mime_to_extension_block_124
  jmp std.mime.types.mime_to_extension_block_128
std.mime.types.mime_to_extension_block_124:
  jmp std.mime.types.mime_to_extension_block_124
  movq [rel str_const_113], rcx
  call lm_box_string
  movq rax, [rbp + -536]
  movq $r14, rcx
  movq $1, rdx
  call lm_list_get
  movq [rbp + -536], rcx
  movq $r124, rdx
  call lm_str_concat
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  jmp std.mime.types.mime_to_extension_epilogue
std.mime.types.mime_to_extension_block_128:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -552]
  jmp std.mime.types.mime_to_extension_block_118
std.mime.types.mime_to_extension_block_133:
  movq [rel str_const_114], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -560], rax
  jmp std.mime.types.mime_to_extension_epilogue
std.mime.types.mime_to_extension_epilogue:
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
.Lfunc_end_std.mime.types.mime_to_extension:

.globl std.mime.types.MIMEType.is_audio
std.mime.types.MIMEType.is_audio:
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
std.mime.types.MIMEType.is_audio_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.is_audio_epilogue
std.mime.types.MIMEType.is_audio_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.is_audio:

.globl std.mime.types.MIMEParams.get
std.mime.types.MIMEParams.get:
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
std.mime.types.MIMEParams.get_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.get_epilogue
std.mime.types.MIMEParams.get_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.get:

.globl std.mime.index.mime_to_extension
std.mime.index.mime_to_extension:
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
std.mime.index.mime_to_extension_entry:
std.mime.index.mime_to_extension_block_0:
  movq [rbp + -64], rcx
  call std.mime.types.mime_to_extension
  movq $r1, rax
  jmp std.mime.index.mime_to_extension_epilogue
std.mime.index.mime_to_extension_epilogue:
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
.Lfunc_end_std.mime.index.mime_to_extension:

.globl std.mime.types.to_lower
std.mime.types.to_lower:
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
std.mime.types.to_lower_entry:
std.mime.types.to_lower_block_0:
  movq [rel str_const_115], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq [rel str_const_116], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  movq [rel str_const_117], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  jmp std.mime.types.to_lower_block_5
std.mime.types.to_lower_block_5:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r5, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -96]
  movq [rbp + -96], rax
  testq rax, rax
  jne std.mime.types.to_lower_block_8
  jmp std.mime.types.to_lower_block_35
std.mime.types.to_lower_block_8:
  jmp std.mime.types.to_lower_block_8
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -104]
  movq [rbp + -64], rcx
  movq $1, rdx
  movq [rbp + -104], r8
  call substring
  movq [rbp + -80], rcx
  movq $r11, rdx
  call std.mime.types.index_of
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
  jne std.mime.types.to_lower_block_19
  jmp std.mime.types.to_lower_block_27
std.mime.types.to_lower_block_19:
  jmp std.mime.types.to_lower_block_19
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
  jmp std.mime.types.to_lower_block_30
std.mime.types.to_lower_block_27:
  movq [rbp + -136], rcx
  movq $r11, rdx
  call lm_str_concat
  movq rax, [rbp + -144]
  jmp std.mime.types.to_lower_block_30
std.mime.types.to_lower_block_30:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -152]
  jmp std.mime.types.to_lower_block_5
std.mime.types.to_lower_block_35:
  movq [rbp + -144], rax
  jmp std.mime.types.to_lower_epilogue
std.mime.types.to_lower_epilogue:
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
.Lfunc_end_std.mime.types.to_lower:

.globl std.mime.types.MIMEParams.init
std.mime.types.MIMEParams.init:
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
std.mime.types.MIMEParams.init_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.init_epilogue
std.mime.types.MIMEParams.init_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.init:

.globl std.mime.types.MIMEType.to_string
std.mime.types.MIMEType.to_string:
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
std.mime.types.MIMEType.to_string_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.to_string_epilogue
std.mime.types.MIMEType.to_string_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.to_string:

.globl std.mime.index.parse
std.mime.index.parse:
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
std.mime.index.parse_entry:
std.mime.index.parse_block_0:
  movq [rbp + -64], rcx
  call std.mime.types.parse
  movq $r1, rax
  jmp std.mime.index.parse_epilogue
std.mime.index.parse_epilogue:
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
.Lfunc_end_std.mime.index.parse:

.globl std.mime.types.MIMEParams.to_string
std.mime.types.MIMEParams.to_string:
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
std.mime.types.MIMEParams.to_string_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.to_string_epilogue
std.mime.types.MIMEParams.to_string_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.to_string:

.globl std.mime.index.MIMEParams
std.mime.index.MIMEParams:
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
std.mime.index.MIMEParams_entry:
std.mime.index.MIMEParams_block_0:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -64], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -64], rcx
  call std.mime.types.MIMEParams.init
  movq $0, rax
  jmp std.mime.index.MIMEParams_epilogue
std.mime.index.MIMEParams_epilogue:
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
.Lfunc_end_std.mime.index.MIMEParams:

.globl test_extension_mapping
test_extension_mapping:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 424
test_extension_mapping_entry:
test_extension_mapping_block_0:
  movq [rel str_const_118], rcx
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
  movq [rel str_const_119], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.mime.index.extension_to_mime
  movq [rel str_const_120], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq $r3, rax
  cmpq [rbp + -104], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -112]
  movq [rel str_const_121], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rbp + -112], rcx
  movq [rbp + -120], rdx
  call lm_assert
  movq [rel str_const_122], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call std.mime.index.extension_to_mime
  movq [rel str_const_123], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq $r9, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rel str_const_124], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rbp + -144], rcx
  movq [rbp + -152], rdx
  call lm_assert
  movq [rel str_const_125], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  call std.mime.index.extension_to_mime
  movq [rel str_const_126], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq $r15, rax
  cmpq [rbp + -168], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_127], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rel str_const_128], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -192], rcx
  call std.mime.index.extension_to_mime
  movq [rel str_const_129], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r21, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_130], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_131], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -224], rcx
  call std.mime.index.extension_to_mime
  movq [rel str_const_132], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq $r27, rax
  cmpq [rbp + -232], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_133], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rel str_const_134], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -256], rcx
  call std.mime.index.mime_to_extension
  movq [rel str_const_135], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r33, rax
  cmpq [rbp + -264], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rel str_const_136], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -272], rcx
  movq [rbp + -280], rdx
  call lm_assert
  movq [rel str_const_137], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -288], rcx
  call std.mime.index.mime_to_extension
  movq [rel str_const_138], rcx
  call lm_box_string
  movq rax, [rbp + -296]
  movq $r39, rax
  cmpq [rbp + -296], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -304]
  movq [rel str_const_139], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rcx
  movq [rbp + -312], rdx
  call lm_assert
  movq [rel str_const_140], rcx
  call lm_box_string
  movq rax, [rbp + -320]
  movq [rbp + -320], rcx
  call std.mime.index.mime_to_extension
  movq [rel str_const_141], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq $r45, rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  movq [rel str_const_142], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq [rbp + -336], rcx
  movq [rbp + -344], rdx
  call lm_assert
  movq [rel str_const_143], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -352], rcx
  call std.mime.index.mime_to_extension
  movq [rel str_const_144], rcx
  call lm_box_string
  movq rax, [rbp + -360]
  movq $r51, rax
  cmpq [rbp + -360], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -368]
  movq [rel str_const_145], rcx
  call lm_box_string
  movq rax, [rbp + -376]
  movq [rbp + -368], rcx
  movq [rbp + -376], rdx
  call lm_assert
  movq [rel str_const_146], rcx
  call lm_box_string
  movq rax, [rbp + -384]
  movq [rbp + -384], rcx
  call std.mime.index.mime_to_extension
  movq [rel str_const_147], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq $r57, rax
  cmpq [rbp + -392], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -400]
  movq [rel str_const_148], rcx
  call lm_box_string
  movq rax, [rbp + -408]
  movq [rbp + -400], rcx
  movq [rbp + -408], rdx
  call lm_assert
  movq [rel str_const_149], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -416], rax
  addq $16, rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  movq rax, [rbp + -432]
  movq [rbp + -432], rax
  mov rax, [rax]
  movq rax, [rbp + -440]
  movq [rbp + -440], rcx
  call lm_print_str
  movq $9, rax
  jmp test_extension_mapping_epilogue
test_extension_mapping_epilogue:
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
.Lfunc_end_test_extension_mapping:

.globl std.mime.index.__init__
std.mime.index.__init__:
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
std.mime.index.__init___entry:
  movq $0, rax
  jmp std.mime.index.__init___epilogue
std.mime.index.__init___epilogue:
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
.Lfunc_end_std.mime.index.__init__:

.globl test_classification
test_classification:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 280
test_classification_entry:
test_classification_block_0:
  movq [rel str_const_150], rcx
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
  movq [rel str_const_151], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.mime.index.parse
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rel str_const_152], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -112], rcx
  call std.mime.index.parse
  movq $r7, rax
  movq rax, [rbp + -120]
  movq [rel str_const_153], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -128], rcx
  call std.mime.index.parse
  movq $r11, rax
  movq rax, [rbp + -136]
  movq [rel str_const_154], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq [rbp + -144], rcx
  call std.mime.index.parse
  movq $r15, rax
  movq rax, [rbp + -152]
  movq [rel str_const_155], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -160], rcx
  call std.mime.index.parse
  movq $r19, rax
  movq rax, [rbp + -168]
  movq [rbp + -104], rcx
  call std.mime.types.MIMEType.is_text
  movq $r22, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -176]
  movq [rel str_const_156], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq [rbp + -176], rcx
  movq [rbp + -184], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.mime.types.MIMEType.is_image
  movq $r27, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rel str_const_157], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rcx
  movq [rbp + -200], rdx
  call lm_assert
  movq [rbp + -120], rcx
  call std.mime.types.MIMEType.is_image
  movq $r32, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_158], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -136], rcx
  call std.mime.types.MIMEType.is_audio
  movq $r37, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -224]
  movq [rel str_const_159], rcx
  call lm_box_string
  movq rax, [rbp + -232]
  movq [rbp + -224], rcx
  movq [rbp + -232], rdx
  call lm_assert
  movq [rbp + -152], rcx
  call std.mime.types.MIMEType.is_video
  movq $r42, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -240]
  movq [rel str_const_160], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -240], rcx
  movq [rbp + -248], rdx
  call lm_assert
  movq [rbp + -168], rcx
  call std.mime.types.MIMEType.is_application
  movq $r47, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rel str_const_161], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq [rbp + -256], rcx
  movq [rbp + -264], rdx
  call lm_assert
  movq [rel str_const_162], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  addq $16, rax
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  mov rax, [rax]
  movq rax, [rbp + -296]
  movq [rbp + -296], rcx
  call lm_print_str
  movq $9, rax
  jmp test_classification_epilogue
test_classification_epilogue:
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
.Lfunc_end_test_classification:

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
  sub rsp, 632
test_parsing_entry:
test_parsing_block_0:
  movq [rel str_const_163], rcx
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
  movq [rel str_const_164], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  movq [rbp + -96], rcx
  call std.mime.index.parse
  movq $r3, rax
  movq rax, [rbp + -104]
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -112]
  movq [rbp + -112], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -120]
  movq [rbp + -120], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -128]
  movq [rel str_const_165], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -128], rcx
  movq [rbp + -136], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -152]
  movq [rel str_const_166], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rax
  cmpq [rbp + -160], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -168]
  movq [rel str_const_167], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq [rbp + -168], rcx
  movq [rbp + -176], rdx
  call lm_assert
  movq [rbp + -104], rax
  addq $0, rax
  movq rax, [rbp + -184]
  movq [rbp + -184], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -192]
  movq [rel str_const_168], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -192], rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_169], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rbp + -104], rcx
  call std.mime.types.MIMEType.to_string
  movq [rel str_const_170], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq $r21, rax
  cmpq [rbp + -224], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_171], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_172], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -248], rcx
  call std.mime.index.parse
  movq $r27, rax
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -264]
  movq [rbp + -264], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -280]
  movq [rel str_const_173], rcx
  call lm_box_string
  movq rax, [rbp + -288]
  movq [rbp + -280], rcx
  movq [rbp + -288], rdx
  call lm_assert
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -304]
  movq [rel str_const_174], rcx
  call lm_box_string
  movq rax, [rbp + -312]
  movq [rbp + -304], rax
  cmpq [rbp + -312], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rel str_const_175], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq [rbp + -320], rcx
  movq [rbp + -328], rdx
  call lm_assert
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -336]
  movq [rbp + -336], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -344]
  movq [rel str_const_176], rcx
  call lm_box_string
  movq rax, [rbp + -352]
  movq [rbp + -344], rax
  cmpq [rbp + -352], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -360]
  movq [rel str_const_177], rcx
  call lm_box_string
  movq rax, [rbp + -368]
  movq [rbp + -360], rcx
  movq [rbp + -368], rdx
  call lm_assert
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -376]
  movq [rbp + -376], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -384]
  movq [rel str_const_178], rcx
  call lm_box_string
  movq rax, [rbp + -392]
  movq [rbp + -384], rcx
  movq [rbp + -392], rdx
  call std.mime.types.MIMEParams.get
  movq [rel str_const_179], rcx
  call lm_box_string
  movq rax, [rbp + -400]
  movq $r47, rax
  cmpq [rbp + -400], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -408]
  movq [rel str_const_180], rcx
  call lm_box_string
  movq rax, [rbp + -416]
  movq [rbp + -408], rcx
  movq [rbp + -416], rdx
  call lm_assert
  movq [rbp + -256], rax
  addq $0, rax
  movq rax, [rbp + -424]
  movq [rbp + -424], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -432]
  movq [rel str_const_181], rcx
  call lm_box_string
  movq rax, [rbp + -440]
  movq [rbp + -432], rcx
  movq [rbp + -440], rdx
  call std.mime.types.MIMEParams.get
  movq [rel str_const_182], rcx
  call lm_box_string
  movq rax, [rbp + -448]
  movq $r54, rax
  cmpq [rbp + -448], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -456]
  movq [rel str_const_183], rcx
  call lm_box_string
  movq rax, [rbp + -464]
  movq [rbp + -456], rcx
  movq [rbp + -464], rdx
  call lm_assert
  movq [rel str_const_184], rcx
  call lm_box_string
  movq rax, [rbp + -472]
  movq [rbp + -472], rcx
  call std.mime.index.parse
  movq $r60, rax
  movq rax, [rbp + -480]
  movq [rbp + -480], rax
  addq $0, rax
  movq rax, [rbp + -488]
  movq [rbp + -488], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -496]
  movq [rbp + -496], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -504]
  movq [rel str_const_185], rcx
  call lm_box_string
  movq rax, [rbp + -512]
  movq [rbp + -504], rcx
  movq [rbp + -512], rdx
  call lm_assert
  movq [rel str_const_186], rcx
  call lm_box_string
  movq rax, [rbp + -520]
  movq [rbp + -520], rcx
  call std.mime.index.parse
  movq $r69, rax
  movq rax, [rbp + -528]
  movq [rbp + -528], rax
  addq $0, rax
  movq rax, [rbp + -536]
  movq [rbp + -536], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -544]
  movq [rbp + -544], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -552]
  movq [rel str_const_187], rcx
  call lm_box_string
  movq rax, [rbp + -560]
  movq [rbp + -552], rcx
  movq [rbp + -560], rdx
  call lm_assert
  movq [rel str_const_188], rcx
  call lm_box_string
  movq rax, [rbp + -568]
  movq [rbp + -568], rcx
  call std.mime.index.parse
  movq $r78, rax
  movq rax, [rbp + -576]
  movq [rbp + -576], rax
  addq $0, rax
  movq rax, [rbp + -584]
  movq [rbp + -584], rax
  movzx rax, byte ptr [rax]
  movq rax, [rbp + -592]
  movq [rbp + -592], rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -600]
  movq [rel str_const_189], rcx
  call lm_box_string
  movq rax, [rbp + -608]
  movq [rbp + -600], rcx
  movq [rbp + -608], rdx
  call lm_assert
  movq [rel str_const_190], rcx
  call lm_box_string
  movq rax, [rbp + -616]
  movq [rbp + -616], rax
  addq $16, rax
  movq rax, [rbp + -624]
  movq [rbp + -624], rax
  movq rax, [rbp + -632]
  movq [rbp + -632], rax
  mov rax, [rax]
  movq rax, [rbp + -640]
  movq [rbp + -640], rcx
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

.globl std.mime.types.MIMEType.init
std.mime.types.MIMEType.init:
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
std.mime.types.MIMEType.init_entry:
  movq $0, rax
  jmp std.mime.types.MIMEType.init_epilogue
std.mime.types.MIMEType.init_epilogue:
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
.Lfunc_end_std.mime.types.MIMEType.init:

.globl test_parameters
test_parameters:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 296
test_parameters_entry:
test_parameters_block_0:
  movq [rel str_const_191], rcx
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
  call std.mime.index.MIMEParams
  movq $r2, rax
  movq rax, [rbp + -96]
  movq [rel str_const_192], rcx
  call lm_box_string
  movq rax, [rbp + -104]
  movq [rel str_const_193], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  movq [rbp + -96], rcx
  movq [rbp + -104], rdx
  movq [rbp + -112], r8
  call std.mime.types.MIMEParams.set
  movq [rel str_const_194], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq [rel str_const_195], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq [rbp + -96], rcx
  movq [rbp + -120], rdx
  movq [rbp + -128], r8
  call std.mime.types.MIMEParams.set
  movq [rel str_const_196], rcx
  call lm_box_string
  movq rax, [rbp + -136]
  movq [rbp + -96], rcx
  movq [rbp + -136], rdx
  call std.mime.types.MIMEParams.get
  movq [rel str_const_197], rcx
  call lm_box_string
  movq rax, [rbp + -144]
  movq $r12, rax
  cmpq [rbp + -144], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -152]
  movq [rel str_const_198], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  movq [rbp + -152], rcx
  movq [rbp + -160], rdx
  call lm_assert
  movq [rel str_const_199], rcx
  call lm_box_string
  movq rax, [rbp + -168]
  movq [rbp + -96], rcx
  movq [rbp + -168], rdx
  call std.mime.types.MIMEParams.get
  movq [rel str_const_200], rcx
  call lm_box_string
  movq rax, [rbp + -176]
  movq $r18, rax
  cmpq [rbp + -176], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -184]
  movq [rel str_const_201], rcx
  call lm_box_string
  movq rax, [rbp + -192]
  movq [rbp + -184], rcx
  movq [rbp + -192], rdx
  call lm_assert
  movq [rel str_const_202], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq [rbp + -96], rcx
  movq [rbp + -200], rdx
  call std.mime.types.MIMEParams.has
  movq $r24, rax
  cmpq $18, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  movq [rel str_const_203], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rbp + -208], rcx
  movq [rbp + -216], rdx
  call lm_assert
  movq [rel str_const_204], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  movq [rbp + -96], rcx
  movq [rbp + -224], rdx
  call std.mime.types.MIMEParams.has
  movq $r30, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -232]
  movq [rel str_const_205], rcx
  call lm_box_string
  movq rax, [rbp + -240]
  movq [rbp + -232], rcx
  movq [rbp + -240], rdx
  call lm_assert
  movq [rel str_const_206], rcx
  call lm_box_string
  movq rax, [rbp + -248]
  movq [rbp + -96], rcx
  movq [rbp + -248], rdx
  call std.mime.types.MIMEParams.remove
  movq [rel str_const_207], rcx
  call lm_box_string
  movq rax, [rbp + -256]
  movq [rbp + -96], rcx
  movq [rbp + -256], rdx
  call std.mime.types.MIMEParams.has
  movq $r38, rax
  cmpq $10, rax
  sete al
  movzx eax, al
  movq rax, [rbp + -264]
  movq [rel str_const_208], rcx
  call lm_box_string
  movq rax, [rbp + -272]
  movq [rbp + -264], rcx
  movq [rbp + -272], rdx
  call lm_assert
  movq [rel str_const_209], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq [rbp + -280], rax
  addq $16, rax
  movq rax, [rbp + -288]
  movq [rbp + -288], rax
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  mov rax, [rax]
  movq rax, [rbp + -304]
  movq [rbp + -304], rcx
  call lm_print_str
  movq $9, rax
  jmp test_parameters_epilogue
test_parameters_epilogue:
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
.Lfunc_end_test_parameters:

.globl std.mime.types.MIMEParams.remove
std.mime.types.MIMEParams.remove:
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
std.mime.types.MIMEParams.remove_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.remove_epilogue
std.mime.types.MIMEParams.remove_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.remove:

.globl std.mime.types.MIMEParams.has
std.mime.types.MIMEParams.has:
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
std.mime.types.MIMEParams.has_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.has_epilogue
std.mime.types.MIMEParams.has_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.has:

.globl std.mime.types.split_str
std.mime.types.split_str:
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
std.mime.types.split_str_entry:
std.mime.types.split_str_block_0:
  movq $0, rcx
  call lm_list_new
  movq [rel str_const_216], rcx
  call lm_box_string
  movq rax, [rbp + -80]
  jmp std.mime.types.split_str_block_6
std.mime.types.split_str_block_6:
  movq [rbp + -64], rcx
  call lm_list_len
  movq $1, rax
  cmpq $r7, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -88]
  movq [rbp + -88], rax
  testq rax, rax
  jne std.mime.types.split_str_block_9
  jmp std.mime.types.split_str_block_32
std.mime.types.split_str_block_9:
  jmp std.mime.types.split_str_block_9
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
  jne std.mime.types.split_str_block_15
  jmp std.mime.types.split_str_block_19
std.mime.types.split_str_block_15:
  jmp std.mime.types.split_str_block_15
  movq $r2, rcx
  movq [rbp + -80], rdx
  call lm_list_append
  movq [rel str_const_217], rcx
  call lm_box_string
  movq rax, [rbp + -112]
  jmp std.mime.types.split_str_block_27
std.mime.types.split_str_block_19:
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
  jmp std.mime.types.split_str_block_27
std.mime.types.split_str_block_27:
  movq $1, rax
  addq $9, rax
  movq rax, [rbp + -144]
  jmp std.mime.types.split_str_block_6
std.mime.types.split_str_block_32:
  movq $r2, rcx
  movq [rbp + -136], rdx
  call lm_list_append
  movq $r2, rax
  jmp std.mime.types.split_str_epilogue
std.mime.types.split_str_epilogue:
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
.Lfunc_end_std.mime.types.split_str:

.globl std.mime.types.parse
std.mime.types.parse:
  push rbp
  mov rbp, rsp
  push rbx
  push rsi
  push rdi
  push r12
  push r13
  push r14
  push r15
  sub rsp, 360
  mov [rbp + -64], rcx
std.mime.types.parse_entry:
std.mime.types.parse_block_0:
  movq [rbp + -64], rcx
  call std.mime.types.trim
  movq [rel str_const_218], rcx
  call lm_box_string
  movq rax, [rbp + -72]
  movq $r1, rax
  cmpq [rbp + -72], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -80]
  movq [rbp + -80], rax
  testq rax, rax
  jne std.mime.types.parse_block_5
  jmp std.mime.types.parse_block_13
std.mime.types.parse_block_5:
  jmp std.mime.types.parse_block_5
  movq [rel str_const_219], rcx
  call lm_box_string
  movq rax, [rbp + -88]
  movq [rel str_const_220], rcx
  call lm_box_string
  movq rax, [rbp + -96]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -104], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -104], rcx
  call std.mime.types.MIMEParams.init
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -112], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -112], rcx
  movq [rbp + -88], rdx
  movq [rbp + -96], r8
  movq [rbp + -104], r9
  call std.mime.types.MIMEType.init
  movq [rbp + -112], rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_block_13:
  movq [rel str_const_221], rcx
  call lm_box_string
  movq rax, [rbp + -120]
  movq $r1, rcx
  movq [rbp + -120], rdx
  call std.mime.types.split_str
  movq $r14, rcx
  movq $1, rdx
  call lm_list_get
  movq $r17, rcx
  call std.mime.types.trim
  movq [rel str_const_222], rcx
  call lm_box_string
  movq rax, [rbp + -128]
  movq $r18, rcx
  movq [rbp + -128], rdx
  call std.mime.types.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -136]
  movq $r21, rax
  cmpq [rbp + -136], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -144]
  movq [rbp + -144], rax
  testq rax, rax
  jne std.mime.types.parse_block_27
  jmp std.mime.types.parse_block_35
std.mime.types.parse_block_27:
  jmp std.mime.types.parse_block_27
  movq [rel str_const_223], rcx
  call lm_box_string
  movq rax, [rbp + -152]
  movq [rel str_const_224], rcx
  call lm_box_string
  movq rax, [rbp + -160]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -168], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -168], rcx
  call std.mime.types.MIMEParams.init
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -176], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -176], rcx
  movq [rbp + -152], rdx
  movq [rbp + -160], r8
  movq [rbp + -168], r9
  call std.mime.types.MIMEType.init
  movq [rbp + -176], rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_block_35:
  movq $r18, rcx
  movq $1, rdx
  movq $r21, r8
  call substring
  movq $r35, rcx
  call std.mime.types.trim
  movq $r36, rcx
  call std.mime.types.to_lower
  movq $r21, rax
  addq $9, rax
  movq rax, $r41
  movq $r18, rcx
  call lm_list_len
  movq $r18, rcx
  movq $r41, rdx
  movq $r42, r8
  call substring
  movq $r43, rcx
  call std.mime.types.trim
  movq $r44, rcx
  call std.mime.types.to_lower
  movq [rel str_const_225], rcx
  call lm_box_string
  movq rax, [rbp + -184]
  movq $r37, rax
  cmpq [rbp + -184], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -192]
  movq [rbp + -192], rax
  testq rax, rax
  jne std.mime.types.parse_block_56
  jmp std.mime.types.parse_block_52
std.mime.types.parse_block_52:
  jmp std.mime.types.parse_block_52
  movq [rel str_const_226], rcx
  call lm_box_string
  movq rax, [rbp + -200]
  movq $r45, rax
  cmpq [rbp + -200], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -208]
  jmp std.mime.types.parse_block_56
std.mime.types.parse_block_56:
  movq [rbp + -208], rax
  testq rax, rax
  jne std.mime.types.parse_block_57
  jmp std.mime.types.parse_block_65
std.mime.types.parse_block_57:
  jmp std.mime.types.parse_block_57
  movq [rel str_const_227], rcx
  call lm_box_string
  movq rax, [rbp + -216]
  movq [rel str_const_228], rcx
  call lm_box_string
  movq rax, [rbp + -224]
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -232], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -232], rcx
  call std.mime.types.MIMEParams.init
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -240], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -240], rcx
  movq [rbp + -216], rdx
  movq [rbp + -224], r8
  movq [rbp + -232], r9
  call std.mime.types.MIMEType.init
  movq [rbp + -240], rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_block_65:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -248], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -248], rcx
  call std.mime.types.MIMEParams.init
  jmp std.mime.types.parse_block_70
std.mime.types.parse_block_70:
  movq $r14, rcx
  call lm_list_len
  movq $9, rax
  cmpq $r64, rax
  setl al
  movzx eax, al
  movq rax, [rbp + -256]
  movq [rbp + -256], rax
  testq rax, rax
  jne std.mime.types.parse_block_73
  jmp std.mime.types.parse_block_141
std.mime.types.parse_block_73:
  jmp std.mime.types.parse_block_73
  movq $r14, rcx
  movq $9, rdx
  call lm_list_get
  movq $r67, rcx
  call std.mime.types.trim
  movq [rel str_const_229], rcx
  call lm_box_string
  movq rax, [rbp + -264]
  movq $r68, rax
  cmpq [rbp + -264], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -272]
  movq [rbp + -272], rax
  testq rax, rax
  jne std.mime.types.parse_block_79
  jmp std.mime.types.parse_block_136
std.mime.types.parse_block_79:
  jmp std.mime.types.parse_block_79
  movq [rel str_const_230], rcx
  call lm_box_string
  movq rax, [rbp + -280]
  movq $r68, rcx
  movq [rbp + -280], rdx
  call std.mime.types.index_of
  movq $9, rax
  negq rax
  movq rax, [rbp + -288]
  movq $r74, rax
  cmpq [rbp + -288], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -296]
  movq [rbp + -296], rax
  testq rax, rax
  jne std.mime.types.parse_block_86
  jmp std.mime.types.parse_block_135
std.mime.types.parse_block_86:
  jmp std.mime.types.parse_block_86
  movq $r68, rcx
  movq $1, rdx
  movq $r74, r8
  call substring
  movq $r81, rcx
  call std.mime.types.trim
  movq $r82, rcx
  call std.mime.types.to_lower
  movq $r74, rax
  addq $9, rax
  movq rax, $r87
  movq $r68, rcx
  call lm_list_len
  movq $r68, rcx
  movq $r87, rdx
  movq $r88, r8
  call substring
  movq $r89, rcx
  call std.mime.types.trim
  movq [rel str_const_231], rcx
  call lm_box_string
  movq rax, [rbp + -304]
  movq $r83, rax
  cmpq [rbp + -304], rax
  setne al
  movzx eax, al
  movq rax, [rbp + -312]
  movq [rbp + -312], rax
  testq rax, rax
  jne std.mime.types.parse_block_101
  jmp std.mime.types.parse_block_134
std.mime.types.parse_block_101:
  jmp std.mime.types.parse_block_101
  movq $r90, rcx
  call lm_list_len
  movq $r97, rax
  cmpq $17, rax
  setge al
  movzx eax, al
  movq rax, [rbp + -320]
  movq [rbp + -320], rax
  testq rax, rax
  jne std.mime.types.parse_block_106
  jmp std.mime.types.parse_block_113
std.mime.types.parse_block_106:
  jmp std.mime.types.parse_block_106
  movq $r90, rcx
  movq $1, rdx
  movq $9, r8
  call substring
  movq [rel str_const_232], rcx
  call lm_box_string
  movq rax, [rbp + -328]
  movq $r102, rax
  cmpq [rbp + -328], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -336]
  jmp std.mime.types.parse_block_113
std.mime.types.parse_block_113:
  movq [rbp + -336], rax
  testq rax, rax
  jne std.mime.types.parse_block_115
  jmp std.mime.types.parse_block_124
std.mime.types.parse_block_115:
  jmp std.mime.types.parse_block_115
  movq $r90, rcx
  call lm_list_len
  movq $r105, rax
  subq $9, rax
  movq rax, $r107
  movq $r90, rcx
  call lm_list_len
  movq $r90, rcx
  movq $r107, rdx
  movq $r108, r8
  call substring
  movq [rel str_const_233], rcx
  call lm_box_string
  movq rax, [rbp + -344]
  movq $r109, rax
  cmpq [rbp + -344], rax
  sete al
  movzx eax, al
  movq rax, [rbp + -352]
  jmp std.mime.types.parse_block_124
std.mime.types.parse_block_124:
  movq [rbp + -352], rax
  testq rax, rax
  jne std.mime.types.parse_block_125
  jmp std.mime.types.parse_block_132
std.mime.types.parse_block_125:
  jmp std.mime.types.parse_block_125
  movq $r90, rcx
  call lm_list_len
  movq $r114, rax
  subq $9, rax
  movq rax, $r116
  movq $r90, rcx
  movq $9, rdx
  movq $r116, r8
  call substring
  jmp std.mime.types.parse_block_132
std.mime.types.parse_block_132:
  movq [rbp + -248], rcx
  movq $r83, rdx
  movq $r117, r8
  call std.mime.types.MIMEParams.add
  jmp std.mime.types.parse_block_134
std.mime.types.parse_block_134:
  jmp std.mime.types.parse_block_135
std.mime.types.parse_block_135:
  jmp std.mime.types.parse_block_136
std.mime.types.parse_block_136:
  movq $9, rax
  addq $9, rax
  movq rax, [rbp + -360]
  jmp std.mime.types.parse_block_70
std.mime.types.parse_block_141:
  # Bump Allocation: 16 bytes
  mov rax, [rel heap_ptr]
  mov [rbp + -368], rax
  add rax, 16
  mov [rel heap_ptr], rax
  movq [rbp + -368], rcx
  movq $r37, rdx
  movq $r45, r8
  movq [rbp + -248], r9
  call std.mime.types.MIMEType.init
  movq [rbp + -368], rax
  jmp std.mime.types.parse_epilogue
std.mime.types.parse_epilogue:
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
.Lfunc_end_std.mime.types.parse:

.globl std.mime.types.MIMEParams.set
std.mime.types.MIMEParams.set:
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
std.mime.types.MIMEParams.set_entry:
  movq $0, rax
  jmp std.mime.types.MIMEParams.set_epilogue
std.mime.types.MIMEParams.set_epilogue:
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
.Lfunc_end_std.mime.types.MIMEParams.set:

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
