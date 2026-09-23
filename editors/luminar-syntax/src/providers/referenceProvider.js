const vscode = require("vscode");

/**
 * Provides "Find All References" functionality.
 * Finds all occurrences of a symbol in the document.
 */
class LuminarReferenceProvider {
  provideReferences(document, position, context, token) {
    const wordRange = document.getWordRangeAtPosition(position, /[A-Za-z_][A-Za-z0-9_]*/);
    if (!wordRange) return [];

    const word = document.getText(wordRange);
    const text = document.getText();
    const references = [];

    // Find all occurrences of the word
    const pattern = new RegExp(`\\b${word}\\b`, 'g');
    let match;
    
    while ((match = pattern.exec(text)) !== null) {
      const pos = document.positionAt(match.index);
      const endPos = document.positionAt(match.index + word.length);
      const range = new vscode.Range(pos, endPos);
      
      // Include the definition if context.includeDeclaration is true
      if (context.includeDeclaration || !this.isDefinition(document, pos, word)) {
        references.push(new vscode.Location(document.uri, range));
      }
    }

    return references;
  }

  /**
   * Check if the position is a definition (fn, class, type, var, etc.)
   */
  isDefinition(document, position, word) {
    const line = document.lineAt(position.line).text;
    const beforeWord = line.substring(0, position.character);
    
    // Check if preceded by definition keywords
    return /\b(fn|class|type|module|var|const|trait|enum|impl)\s+$/.test(beforeWord);
  }
}

module.exports = { LuminarReferenceProvider };
