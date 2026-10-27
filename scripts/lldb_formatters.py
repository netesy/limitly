# LLDB Pretty-Printer Formatters for Lymar AOT Compiled Objects
import lldb

def LmString_Summary(valobj, internal_dict):
    try:
        header_type = valobj.GetChildMemberWithName("header").GetChildMemberWithName("type_id").GetValueAsUnsigned()
        length = valobj.GetChildMemberWithName("len").GetValueAsUnsigned()
        data_ptr = valobj.GetChildMemberWithName("data")
        if data_ptr.IsValid():
            error = lldb.SBError()
            process = valobj.GetProcess()
            data_bytes = process.ReadMemory(data_ptr.GetValueAsUnsigned(), min(length, 256), error)
            if error.Success():
                return f'"{data_bytes.decode("utf-8", errors="replace")}"'
    except Exception:
        pass
    return "<LmString>"

def LmList_Summary(valobj, internal_dict):
    try:
        size = valobj.GetChildMemberWithName("size").GetValueAsUnsigned()
        capacity = valobj.GetChildMemberWithName("capacity").GetValueAsUnsigned()
        return f"LmList(size={size}, capacity={capacity})"
    except Exception:
        pass
    return "<LmList>"

def LmFrame_Summary(valobj, internal_dict):
    try:
        name_ptr = valobj.GetChildMemberWithName("name")
        field_count = valobj.GetChildMemberWithName("field_count").GetValueAsSigned()
        process = valobj.GetProcess()
        error = lldb.SBError()
        name_str = process.ReadCStringFromMemory(name_ptr.GetValueAsUnsigned(), 256, error)
        if error.Success() and name_str:
            return f"LmFrame({name_str}, fields={field_count})"
    except Exception:
        pass
    return "<LmFrame>"

def __lldb_init_module(debugger, dict):
    debugger.HandleCommand('type summary add -F lldb_formatters.LmString_Summary LmStringHeader')
    debugger.HandleCommand('type summary add -F lldb_formatters.LmList_Summary LmList')
    debugger.HandleCommand('type summary add -F lldb_formatters.LmFrame_Summary LmFrame')
