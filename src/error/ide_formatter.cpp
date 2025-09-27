#include "ide_formatter.hh"
#include <sstream>
#include <iomanip>
#include <chrono>
#include <algorithm>
#include <regex>
#include <functional>

namespace ErrorHandling {

IDEFormatter::IDEOptions IDEFormatter::getDefaultOptions() {
    return IDEOptions();
}

std::string IDEFormatter::formatErrorMessage(
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    switch (options.format) {
        case OutputFormat::JSON:
            return formatAsJSON(errorMessage, options);
        case OutputFormat::XML:
            return formatAsXML(errorMessage, options);
        case OutputFormat::LSP:
            return formatAsLSP(errorMessage, options);
        case OutputFormat::SARIF:
            return formatAsSARIF(errorMessage, options);
        case OutputFormat::COMPACT:
            return formatAsCompact(errorMessage, options);
        default:
            return formatAsJSON(errorMessage, options);
    }
}

std::string IDEFormatter::formatErrorBatch(
    const std::vector<ErrorMessage>& errorMessages,
    const IDEOptions& options)
{
    switch (options.format) {
        case OutputFormat::JSON:
            return formatBatchAsJSON(errorMessages, options);
        case OutputFormat::XML:
            return formatBatchAsXML(errorMessages, options);
        case OutputFormat::LSP:
            return formatBatchAsLSP(errorMessages, options);
        case OutputFormat::SARIF:
            return formatBatchAsSARIF(errorMessages, options);
        case OutputFormat::COMPACT:
            {
                std::ostringstream result;
                for (size_t i = 0; i < errorMessages.size(); ++i) {
                    if (i > 0) result << "\n";
                    result << formatAsCompact(errorMessages[i], options);
                }
                return result.str();
            }
        default:
            return formatBatchAsJSON(errorMessages, options);
    }
}

void IDEFormatter::writeErrorMessage(
    std::ostream& out,
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    out << formatErrorMessage(errorMessage, options);
}

void IDEFormatter::writeErrorBatch(
    std::ostream& out,
    const std::vector<ErrorMessage>& errorMessages,
    const IDEOptions& options)
{
    out << formatErrorBatch(errorMessages, options);
}

std::string IDEFormatter::getSeverityLevel(InterpretationStage stage) {
    switch (stage) {
        case InterpretationStage::SCANNING:
        case InterpretationStage::PARSING:
        case InterpretationStage::SEMANTIC:
        case InterpretationStage::BYTECODE:
            return "error";
        case InterpretationStage::INTERPRETING:
            return "error";
        default:
            return "error";
    }
}

std::string IDEFormatter::getErrorCategory(const std::string& errorType) {
    if (errorType.find("Syntax") != std::string::npos) {
        return "syntax";
    } else if (errorType.find("Semantic") != std::string::npos || 
               errorType.find("Type") != std::string::npos) {
        return "semantic";
    } else if (errorType.find("Runtime") != std::string::npos) {
        return "runtime";
    } else if (errorType.find("Lexical") != std::string::npos) {
        return "lexical";
    } else {
        return "general";
    }
}

std::string IDEFormatter::generateErrorId(const ErrorMessage& errorMessage) {
    return errorMessage.errorCode + "_" + generateHash(errorMessage);
}

// JSON formatting implementation

std::string IDEFormatter::formatAsJSON(
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    std::ostringstream json;
    json << "{\n";
    
    // Basic error information
    json << "  \"id\": \"" << escapeJSON(generateErrorId(errorMessage)) << "\",\n";
    json << "  \"code\": \"" << escapeJSON(errorMessage.errorCode) << "\",\n";
    json << "  \"type\": \"" << escapeJSON(errorMessage.errorType) << "\",\n";
    json << "  \"severity\": \"" << escapeJSON(getSeverityLevel(errorMessage.stage)) << "\",\n";
    json << "  \"category\": \"" << escapeJSON(getErrorCategory(errorMessage.errorType)) << "\",\n";
    json << "  \"message\": \"" << escapeJSON(errorMessage.description) << "\",\n";
    
    // Location information
    if (!errorMessage.filePath.empty()) {
        json << "  \"file\": \"" << escapeJSON(errorMessage.filePath) << "\",\n";
    }
    if (errorMessage.line > 0) {
        json << "  \"line\": " << errorMessage.line << ",\n";
    }
    if (errorMessage.column > 0) {
        json << "  \"column\": " << errorMessage.column << ",\n";
    }
    
    // Problematic token
    if (!errorMessage.problematicToken.empty()) {
        json << "  \"token\": \"" << escapeJSON(errorMessage.problematicToken) << "\",\n";
    }
    
    // Enhanced information
    if (options.includeHints) {
        if (!errorMessage.hint.empty()) {
            json << "  \"hint\": \"" << escapeJSON(errorMessage.hint) << "\",\n";
        }
        if (!errorMessage.suggestion.empty()) {
            json << "  \"suggestion\": \"" << escapeJSON(errorMessage.suggestion) << "\",\n";
        }
        if (!errorMessage.causedBy.empty()) {
            json << "  \"causedBy\": \"" << escapeJSON(errorMessage.causedBy) << "\",\n";
        }
    }
    
    // Source context
    if (options.includeSourceContext && !errorMessage.contextLines.empty()) {
        json << "  \"context\": " << vectorToJSONArray(errorMessage.contextLines) << ",\n";
    }
    
    // Metadata
    if (options.includeMetadata) {
        json << "  \"metadata\": {\n";
        json << "    \"tool\": \"" << escapeJSON(options.toolName) << "\",\n";
        json << "    \"version\": \"" << escapeJSON(options.toolVersion) << "\",\n";
        json << "    \"timestamp\": \"" << escapeJSON(getCurrentTimestamp()) << "\",\n";
        json << "    \"stage\": \"" << static_cast<int>(errorMessage.stage) << "\"\n";
        json << "  }\n";
    } else {
        // Remove trailing comma from last element
        std::string content = json.str();
        if (content.back() == '\n' && content[content.length()-2] == ',') {
            json.str("");
            json << content.substr(0, content.length()-2) << "\n";
        }
    }
    
    json << "}";
    return json.str();
}

std::string IDEFormatter::formatBatchAsJSON(
    const std::vector<ErrorMessage>& errorMessages,
    const IDEOptions& options)
{
    std::ostringstream json;
    json << "{\n";
    json << "  \"errors\": [\n";
    
    for (size_t i = 0; i < errorMessages.size(); ++i) {
        if (i > 0) json << ",\n";
        
        // Indent the individual error JSON
        std::string errorJson = formatAsJSON(errorMessages[i], options);
        std::istringstream stream(errorJson);
        std::string line;
        bool first = true;
        
        while (std::getline(stream, line)) {
            if (!first) json << "\n";
            json << "    " << line;
            first = false;
        }
    }
    
    json << "\n  ],\n";
    json << "  \"summary\": {\n";
    json << "    \"totalErrors\": " << errorMessages.size() << ",\n";
    json << "    \"tool\": \"" << escapeJSON(options.toolName) << "\",\n";
    json << "    \"version\": \"" << escapeJSON(options.toolVersion) << "\",\n";
    json << "    \"timestamp\": \"" << escapeJSON(getCurrentTimestamp()) << "\"\n";
    json << "  }\n";
    json << "}";
    
    return json.str();
}

// XML formatting implementation

std::string IDEFormatter::formatAsXML(
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    std::ostringstream xml;
    
    std::map<std::string, std::string> errorAttrs;
    errorAttrs["id"] = generateErrorId(errorMessage);
    errorAttrs["code"] = errorMessage.errorCode;
    errorAttrs["type"] = errorMessage.errorType;
    errorAttrs["severity"] = getSeverityLevel(errorMessage.stage);
    errorAttrs["category"] = getErrorCategory(errorMessage.errorType);
    
    xml << "<error";
    for (const auto& attr : errorAttrs) {
        xml << " " << attr.first << "=\"" << escapeXML(attr.second) << "\"";
    }
    xml << ">\n";
    
    xml << "  " << createXMLElement("message", errorMessage.description) << "\n";
    
    // Location information
    if (!errorMessage.filePath.empty() || errorMessage.line > 0) {
        xml << "  <location";
        if (!errorMessage.filePath.empty()) {
            xml << " file=\"" << escapeXML(errorMessage.filePath) << "\"";
        }
        if (errorMessage.line > 0) {
            xml << " line=\"" << errorMessage.line << "\"";
        }
        if (errorMessage.column > 0) {
            xml << " column=\"" << errorMessage.column << "\"";
        }
        xml << "/>\n";
    }
    
    // Problematic token
    if (!errorMessage.problematicToken.empty()) {
        xml << "  " << createXMLElement("token", errorMessage.problematicToken) << "\n";
    }
    
    // Enhanced information
    if (options.includeHints) {
        if (!errorMessage.hint.empty()) {
            xml << "  " << createXMLElement("hint", errorMessage.hint) << "\n";
        }
        if (!errorMessage.suggestion.empty()) {
            xml << "  " << createXMLElement("suggestion", errorMessage.suggestion) << "\n";
        }
        if (!errorMessage.causedBy.empty()) {
            xml << "  " << createXMLElement("causedBy", errorMessage.causedBy) << "\n";
        }
    }
    
    // Source context
    if (options.includeSourceContext && !errorMessage.contextLines.empty()) {
        xml << "  <context>\n";
        for (const auto& line : errorMessage.contextLines) {
            xml << "    " << createXMLElement("line", line) << "\n";
        }
        xml << "  </context>\n";
    }
    
    // Metadata
    if (options.includeMetadata) {
        std::map<std::string, std::string> metaAttrs;
        metaAttrs["tool"] = options.toolName;
        metaAttrs["version"] = options.toolVersion;
        metaAttrs["timestamp"] = getCurrentTimestamp();
        metaAttrs["stage"] = std::to_string(static_cast<int>(errorMessage.stage));
        
        xml << "  <metadata";
        for (const auto& attr : metaAttrs) {
            xml << " " << attr.first << "=\"" << escapeXML(attr.second) << "\"";
        }
        xml << "/>\n";
    }
    
    xml << "</error>";
    return xml.str();
}

std::string IDEFormatter::formatBatchAsXML(
    const std::vector<ErrorMessage>& errorMessages,
    const IDEOptions& options)
{
    std::ostringstream xml;
    xml << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>\n";
    xml << "<errors";
    xml << " totalErrors=\"" << errorMessages.size() << "\"";
    xml << " tool=\"" << escapeXML(options.toolName) << "\"";
    xml << " version=\"" << escapeXML(options.toolVersion) << "\"";
    xml << " timestamp=\"" << escapeXML(getCurrentTimestamp()) << "\"";
    xml << ">\n";
    
    for (const auto& errorMessage : errorMessages) {
        std::string errorXml = formatAsXML(errorMessage, options);
        // Indent the XML
        std::istringstream stream(errorXml);
        std::string line;
        while (std::getline(stream, line)) {
            xml << "  " << line << "\n";
        }
    }
    
    xml << "</errors>";
    return xml.str();
}

// LSP formatting implementation

std::string IDEFormatter::formatAsLSP(
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    std::ostringstream lsp;
    lsp << "{\n";
    
    // LSP diagnostic format
    lsp << "  \"range\": {\n";
    lsp << "    \"start\": " << createLSPPosition(errorMessage.line, errorMessage.column) << ",\n";
    lsp << "    \"end\": " << createLSPPosition(errorMessage.line, errorMessage.column + 1) << "\n";
    lsp << "  },\n";
    
    lsp << "  \"severity\": " << getLSPSeverity(errorMessage.stage) << ",\n";
    lsp << "  \"code\": \"" << escapeJSON(errorMessage.errorCode) << "\",\n";
    lsp << "  \"source\": \"" << escapeJSON(options.toolName) << "\",\n";
    lsp << "  \"message\": \"" << escapeJSON(errorMessage.description) << "\"";
    
    // Add related information if available
    if (options.includeHints && (!errorMessage.hint.empty() || !errorMessage.suggestion.empty())) {
        lsp << ",\n  \"relatedInformation\": [\n";
        
        bool first = true;
        if (!errorMessage.hint.empty()) {
            if (!first) lsp << ",\n";
            lsp << "    {\n";
            lsp << "      \"location\": {\n";
            lsp << "        \"uri\": \"file://" << escapeJSON(errorMessage.filePath) << "\",\n";
            lsp << "        \"range\": {\n";
            lsp << "          \"start\": " << createLSPPosition(errorMessage.line, errorMessage.column) << ",\n";
            lsp << "          \"end\": " << createLSPPosition(errorMessage.line, errorMessage.column + 1) << "\n";
            lsp << "        }\n";
            lsp << "      },\n";
            lsp << "      \"message\": \"Hint: " << escapeJSON(errorMessage.hint) << "\"\n";
            lsp << "    }";
            first = false;
        }
        
        if (!errorMessage.suggestion.empty()) {
            if (!first) lsp << ",\n";
            lsp << "    {\n";
            lsp << "      \"location\": {\n";
            lsp << "        \"uri\": \"file://" << escapeJSON(errorMessage.filePath) << "\",\n";
            lsp << "        \"range\": {\n";
            lsp << "          \"start\": " << createLSPPosition(errorMessage.line, errorMessage.column) << ",\n";
            lsp << "          \"end\": " << createLSPPosition(errorMessage.line, errorMessage.column + 1) << "\n";
            lsp << "        }\n";
            lsp << "      },\n";
            lsp << "      \"message\": \"Suggestion: " << escapeJSON(errorMessage.suggestion) << "\"\n";
            lsp << "    }";
        }
        
        lsp << "\n  ]";
    }
    
    lsp << "\n}";
    return lsp.str();
}

std::string IDEFormatter::formatBatchAsLSP(
    const std::vector<ErrorMessage>& errorMessages,
    const IDEOptions& options)
{
    std::ostringstream lsp;
    lsp << "[\n";
    
    for (size_t i = 0; i < errorMessages.size(); ++i) {
        if (i > 0) lsp << ",\n";
        
        // Indent the individual diagnostic
        std::string diagnostic = formatAsLSP(errorMessages[i], options);
        std::istringstream stream(diagnostic);
        std::string line;
        bool first = true;
        
        while (std::getline(stream, line)) {
            if (!first) lsp << "\n";
            lsp << "  " << line;
            first = false;
        }
    }
    
    lsp << "\n]";
    return lsp.str();
}

// SARIF formatting implementation

std::string IDEFormatter::formatAsSARIF(
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    std::ostringstream sarif;
    sarif << "{\n";
    sarif << "  \"ruleId\": \"" << escapeJSON(errorMessage.errorCode) << "\",\n";
    sarif << "  \"level\": \"error\",\n";
    sarif << "  \"message\": {\n";
    sarif << "    \"text\": \"" << escapeJSON(errorMessage.description) << "\"\n";
    sarif << "  },\n";
    sarif << "  \"locations\": [\n";
    sarif << "    " << createSARIFLocation(errorMessage) << "\n";
    sarif << "  ]";
    
    if (options.includeHints && (!errorMessage.hint.empty() || !errorMessage.suggestion.empty())) {
        sarif << ",\n  \"fixes\": [\n";
        sarif << "    {\n";
        sarif << "      \"description\": {\n";
        if (!errorMessage.suggestion.empty()) {
            sarif << "        \"text\": \"" << escapeJSON(errorMessage.suggestion) << "\"\n";
        } else {
            sarif << "        \"text\": \"" << escapeJSON(errorMessage.hint) << "\"\n";
        }
        sarif << "      }\n";
        sarif << "    }\n";
        sarif << "  ]";
    }
    
    sarif << "\n}";
    return sarif.str();
}

std::string IDEFormatter::formatBatchAsSARIF(
    const std::vector<ErrorMessage>& errorMessages,
    const IDEOptions& options)
{
    std::ostringstream sarif;
    sarif << "{\n";
    sarif << "  \"version\": \"2.1.0\",\n";
    sarif << "  \"runs\": [\n";
    sarif << "    {\n";
    sarif << "      \"tool\": {\n";
    sarif << "        \"driver\": {\n";
    sarif << "          \"name\": \"" << escapeJSON(options.toolName) << "\",\n";
    sarif << "          \"version\": \"" << escapeJSON(options.toolVersion) << "\"\n";
    sarif << "        }\n";
    sarif << "      },\n";
    sarif << "      \"results\": [\n";
    
    for (size_t i = 0; i < errorMessages.size(); ++i) {
        if (i > 0) sarif << ",\n";
        
        // Indent the individual result
        std::string result = formatAsSARIF(errorMessages[i], options);
        std::istringstream stream(result);
        std::string line;
        bool first = true;
        
        while (std::getline(stream, line)) {
            if (!first) sarif << "\n";
            sarif << "        " << line;
            first = false;
        }
    }
    
    sarif << "\n      ]\n";
    sarif << "    }\n";
    sarif << "  ]\n";
    sarif << "}";
    
    return sarif.str();
}

// Compact formatting implementation

std::string IDEFormatter::formatAsCompact(
    const ErrorMessage& errorMessage,
    const IDEOptions& options)
{
    std::ostringstream compact;
    
    // Format: file:line:column: severity: [code] message
    if (!errorMessage.filePath.empty()) {
        compact << errorMessage.filePath;
        if (errorMessage.line > 0) {
            compact << ":" << errorMessage.line;
            if (errorMessage.column > 0) {
                compact << ":" << errorMessage.column;
            }
        }
        compact << ": ";
    }
    
    compact << getSeverityLevel(errorMessage.stage) << ": ";
    compact << "[" << errorMessage.errorCode << "] ";
    compact << errorMessage.description;
    
    if (!errorMessage.problematicToken.empty()) {
        compact << " (token: '" << errorMessage.problematicToken << "')";
    }
    
    return compact.str();
}

// Helper method implementations

std::string IDEFormatter::escapeJSON(const std::string& str) {
    std::ostringstream escaped;
    for (char c : str) {
        switch (c) {
            case '"': escaped << "\\\""; break;
            case '\\': escaped << "\\\\"; break;
            case '\b': escaped << "\\b"; break;
            case '\f': escaped << "\\f"; break;
            case '\n': escaped << "\\n"; break;
            case '\r': escaped << "\\r"; break;
            case '\t': escaped << "\\t"; break;
            default:
                if (c < 0x20) {
                    escaped << "\\u" << std::hex << std::setw(4) << std::setfill('0') << static_cast<int>(c);
                } else {
                    escaped << c;
                }
                break;
        }
    }
    return escaped.str();
}

std::string IDEFormatter::vectorToJSONArray(const std::vector<std::string>& strings) {
    std::ostringstream array;
    array << "[";
    for (size_t i = 0; i < strings.size(); ++i) {
        if (i > 0) array << ", ";
        array << "\"" << escapeJSON(strings[i]) << "\"";
    }
    array << "]";
    return array.str();
}

std::string IDEFormatter::createJSONObject(const std::map<std::string, std::string>& pairs) {
    std::ostringstream obj;
    obj << "{";
    bool first = true;
    for (const auto& pair : pairs) {
        if (!first) obj << ", ";
        obj << "\"" << escapeJSON(pair.first) << "\": \"" << escapeJSON(pair.second) << "\"";
        first = false;
    }
    obj << "}";
    return obj.str();
}

std::string IDEFormatter::escapeXML(const std::string& str) {
    std::ostringstream escaped;
    for (char c : str) {
        switch (c) {
            case '<': escaped << "&lt;"; break;
            case '>': escaped << "&gt;"; break;
            case '&': escaped << "&amp;"; break;
            case '"': escaped << "&quot;"; break;
            case '\'': escaped << "&apos;"; break;
            default: escaped << c; break;
        }
    }
    return escaped.str();
}

std::string IDEFormatter::createXMLElement(
    const std::string& tagName,
    const std::string& content,
    const std::map<std::string, std::string>& attributes)
{
    std::ostringstream element;
    element << "<" << tagName;
    for (const auto& attr : attributes) {
        element << " " << attr.first << "=\"" << escapeXML(attr.second) << "\"";
    }
    element << ">" << escapeXML(content) << "</" << tagName << ">";
    return element.str();
}

std::string IDEFormatter::createLSPPosition(int line, int column) {
    std::ostringstream pos;
    pos << "{ \"line\": " << (line - 1) << ", \"character\": " << (column - 1) << " }";
    return pos.str();
}

int IDEFormatter::getLSPSeverity(InterpretationStage stage) {
    // LSP severity: 1 = Error, 2 = Warning, 3 = Information, 4 = Hint
    switch (stage) {
        case InterpretationStage::SCANNING:
        case InterpretationStage::PARSING:
        case InterpretationStage::SEMANTIC:
        case InterpretationStage::BYTECODE:
        case InterpretationStage::INTERPRETING:
            return 1; // Error
        default:
            return 1; // Error
    }
}

std::string IDEFormatter::createSARIFLocation(const ErrorMessage& errorMessage) {
    std::ostringstream location;
    location << "{\n";
    location << "      \"physicalLocation\": {\n";
    if (!errorMessage.filePath.empty()) {
        location << "        \"artifactLocation\": {\n";
        location << "          \"uri\": \"" << escapeJSON(errorMessage.filePath) << "\"\n";
        location << "        },\n";
    }
    location << "        \"region\": {\n";
    location << "          \"startLine\": " << errorMessage.line << ",\n";
    location << "          \"startColumn\": " << errorMessage.column << "\n";
    location << "        }\n";
    location << "      }\n";
    location << "    }";
    return location.str();
}

std::string IDEFormatter::createSARIFRule(const ErrorMessage& errorMessage) {
    std::ostringstream rule;
    rule << "{\n";
    rule << "  \"id\": \"" << escapeJSON(errorMessage.errorCode) << "\",\n";
    rule << "  \"shortDescription\": {\n";
    rule << "    \"text\": \"" << escapeJSON(errorMessage.errorType) << "\"\n";
    rule << "  },\n";
    rule << "  \"fullDescription\": {\n";
    rule << "    \"text\": \"" << escapeJSON(errorMessage.description) << "\"\n";
    rule << "  }\n";
    rule << "}";
    return rule.str();
}

std::string IDEFormatter::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t = std::chrono::system_clock::to_time_t(now);
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(
        now.time_since_epoch()) % 1000;
    
    std::ostringstream timestamp;
    timestamp << std::put_time(std::gmtime(&time_t), "%Y-%m-%dT%H:%M:%S");
    timestamp << "." << std::setfill('0') << std::setw(3) << ms.count() << "Z";
    
    return timestamp.str();
}

std::string IDEFormatter::generateHash(const ErrorMessage& errorMessage) {
    // Simple hash based on error content
    std::hash<std::string> hasher;
    std::string content = errorMessage.errorCode + errorMessage.description + 
                         errorMessage.filePath + std::to_string(errorMessage.line);
    size_t hash = hasher(content);
    
    std::ostringstream hashStr;
    hashStr << std::hex << hash;
    return hashStr.str().substr(0, 8); // Take first 8 characters
}

} // namespace ErrorHandling