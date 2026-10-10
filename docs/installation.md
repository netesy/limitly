# Installation and compiler updates

From a checkout with its recursive submodules, use:

```sh
bash scripts/install.sh --prefix "$HOME/.local" --jobs 4
```

The source installer requires Bash, Python 3, Git, Make, a supported C++ toolchain,
and libffi/OpenSSL/zlib development dependencies. Windows uses MSYS2 MinGW64.
It installs the compiler, stdlib, available runtime libraries, and update helper
under `PREFIX/share/lymar`; `PREFIX/bin/lymar` sets `LYMAR_HOME`.

## `lymar up`

`up` updates the compiler distribution; `update` remains Lyra's package dependency
and lockfile command.

```sh
lymar up --check
lymar up
lymar up --version v0.0.1
lymar up --repo netesy/limitly --prefix "$HOME/.local"
```

The default release repository is `lymarlang/lymar`. Latest means GitHub's latest
published stable release; explicit tags can select prereleases. Python 3.9+ and
the Bash launcher used by the installer are required (MSYS2 Bash on Windows).
A checkout invocation defaults to `~/.local`; an installed invocation defaults
to its current prefix. `--check` reads release metadata without changing files.

The updater chooses the host OS and architecture, requires HTTPS and an archive
SHA-256 digest, rejects unsafe archive paths/links/special files, and limits
download/extraction size. It stages the compiler and stdlib together and verifies
both compiler help and actual source execution before activation.

Releases are stored in `PREFIX/share/lymar/releases/TAG-TARGET-DIGEST`.
Activation atomically replaces the launcher, not the running executable.
Previous installations remain available. Failed integrity, extraction, smoke,
or activation checks leave the old launcher active. Existing release directories
are not overwritten. The updater does not modify a Git checkout, run source
builds, publish releases, or remove previous installations.

Checksums establish consistency with the HTTPS release publisher, not an
independent signature or reproducible-build guarantee. System library requirements
must be specified by the publisher. Updating does not install system packages.

## Publisher archive contract

An update requires a **complete distribution**, not a lone compiler executable
or GitHub's automatically generated source archive. Upload one matching archive:

```text
lymar-TAG-x86_64-linux.tar.gz
lymar-TAG-aarch64-macos.tar.gz
lymar-TAG-x86_64-windows.tar.gz
```

Unversioned `lymar-TARGET.tar.gz` names and `.zip` archives are also accepted.
The archive root contains `bin/lymar` (`bin/lymar.exe` on Windows), `std/`, and
`scripts/update.py`, plus the runtime libraries needed by its supported features.
There must be exactly one archive matching the running host. Cross-target AOT
support does not imply that a native release exists for every target.

From a built checkout, package and locally smoke-test a host release:

```sh
python3 scripts/package_release.py --tag v0.0.1 --output build/releases
```

Upload the archive and `SHA256SUMS` to the intended GitHub release, or use GitHub
asset metadata providing `digest: sha256:...`. The packager includes existing
runtime helpers and AOT archives; it does not build missing dependencies or bundle
all system shared libraries. Validate the archive on a clean target machine before
publishing. Native precompiled modules are optional via `--include-precompiled`;
they still undergo normal source/target/ABI validation on load.

The repository does not currently define a release-upload CI workflow. Creating
this archive is not evidence that a downloadable release was published. The live
GitHub API must be reachable to check or install a release.
