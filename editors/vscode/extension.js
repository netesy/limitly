const vscode = require('vscode');
const cp = require('child_process');
const path = require('path');
const fs = require('fs');

function resolveLymarPath(context) {
    const config = vscode.workspace.getConfiguration('lymar');
    let lymarPath = config.get('serverPath', '');
    if (lymarPath) return lymarPath;

    // Search workspace for the binary
    const workspaceFolder = vscode.workspace.workspaceFolders?.[0];
    if (workspaceFolder) {
        const binName = process.platform === 'win32' ? 'lymar.exe' : 'lymar';
        const candidates = [
            path.join(workspaceFolder.uri.fsPath, 'bin', binName),
            path.join(workspaceFolder.uri.fsPath, binName),
        ];
        for (const c of candidates) {
            if (fs.existsSync(c)) return c;
        }
    }

    // Fall back to PATH
    return 'lymar';
}

function activateLSP(context) {
    let client;
    try {
        const { LanguageClient, TransportKind } = require('vscode-languageclient/node');
        const lymarPath = resolveLymarPath(context);

        const serverOptions = {
            run: { command: lymarPath, args: ['-lsp'], transport: TransportKind.stdio },
            debug: { command: lymarPath, args: ['-lsp'], transport: TransportKind.stdio },
        };

        const clientOptions = {
            documentSelector: [{ scheme: 'file', language: 'lymar' }],
            synchronize: { fileEvents: vscode.workspace.createFileSystemWatcher('**/*.lm') },
        };

        client = new LanguageClient(
            'lymarLanguageServer',
            'Lymar Language Server',
            serverOptions,
            clientOptions
        );
        context.subscriptions.push(client.start());
    } catch (e) {
        // vscode-languageclient not bundled; start server manually
        const lymarPath = resolveLymarPath(context);
        vscode.window.setStatusBarMessage(`Lymar LSP: install vscode-languageclient or use F5 with ${lymarPath} -lsp`, 5000);
    }
}

function activateDAP(context) {
    const provider = class extends vscode.DebugAdapterDescriptorFactory {
        createDebugAdapterDescriptor(session, executable) {
            const lymarPath = resolveLymarPath(context);
            const config = session.configuration;
            if (config.mode === 'aot' || config.mode === 'lldb') {
                return new vscode.DebugAdapterExecutable(lymarPath, ['-dap', '--port', '0']);
            }
            return new vscode.DebugAdapterExecutable(lymarPath, ['-dap']);
        }
    };

    const factory = new class {
        createDebugAdapterDescriptor(_session) {
            const lymarPath = resolveLymarPath(context);
            return new vscode.DebugAdapterExecutable(lymarPath, ['-dap']);
        }
    };

    context.subscriptions.push(
        vscode.debug.registerDebugAdapterDescriptorFactory('lymar', factory)
    );

    // Resolver that fills in defaults
    context.subscriptions.push(
        vscode.debug.registerDebugConfigurationProvider('lymar', {
            resolveDebugConfiguration(folder, config) {
                if (!config.program) {
                    const editor = vscode.window.activeTextEditor;
                    if (editor && editor.document.languageId === 'lymar') {
                        config.program = editor.document.uri.fsPath;
                    }
                }
                if (!config.type) {
                    config.type = 'lymar';
                    config.request = 'launch';
                    config.name = 'Debug Lymar File';
                    config.stopOnEntry = true;
                    config.mode = 'vm';
                }
                config.lymarPath = resolveLymarPath(context);
                return config;
            }
        })
    );
}

function activate(context) {
    activateLSP(context);
    activateDAP(context);
}

function deactivate() {}

module.exports = { activate, deactivate };
