const vscode = require("vscode");

/**
 * Provides "Go to Definition" and "Peek Definition" functionality.
 * This is a simplified implementation that searches for function and class definitions.
 */
class LuminarDefinitionProvider {
  provideDefinition(document, position, token) {
    const wordRange = document.getWordRangeAtPosition(position, /[A-Za-z_][A-Za-z0-9_]*/);
    if (!wordRange) return null;

    const word = document.getText(wordRange);
    const text = document.getText();
    const lines = text.split(/\r?\n/);

    // Search for function definitions: fn name(
    const fnPattern = new RegExp(`\\bfn\\s+${word}\\s*\\(`, 'g');
    let match = fnPattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    // Search for class or frame definitions: class Name or frame Name
    const classPattern = new RegExp(`\\b(?:class|frame)\\s+${word}\\b`, 'g');
    match = classPattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    // Search for type definitions: type Name
    const typePattern = new RegExp(`\\btype\\s+${word}\\b`, 'g');
    match = typePattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    // Search for module definitions: module Name
    const modulePattern = new RegExp(`\\bmodule\\s+${word}\\b`, 'g');
    match = modulePattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    // Search for variable or constant declarations: var name, val name, const name
    const varPattern = new RegExp(`\\b(?:var|val|const)\\s+${word}\\b`, 'g');
    match = varPattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    // Search for enum definitions: enum Name
    const enumPattern = new RegExp(`\\benum\\s+${word}\\b`, 'g');
    match = enumPattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    // Search for trait definitions: trait Name
    const traitPattern = new RegExp(`\\btrait\\s+${word}\\b`, 'g');
    match = traitPattern.exec(text);
    if (match) {
      const pos = document.positionAt(match.index);
      return new vscode.Location(document.uri, pos);
    }

    return null;
  }
}

module.exports = { LuminarDefinitionProvider };
