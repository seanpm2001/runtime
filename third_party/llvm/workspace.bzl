"""Provides the repository macro to import LLVM."""

load("//third_party:repo.bzl", "tfrt_http_archive")

def repo(name):
    """Imports LLVM."""
    LLVM_COMMIT = "a2639dcbe613bb2e219a50171f322d7ac1dc8de1"
    LLVM_SHA256 = "6b8eee6dadd8d02bad73fba8ec12d55ccf567b0b44b5be8a674c16c95bfc4b40"

    tfrt_http_archive(
        name = name,
        build_file = "//third_party/llvm:BUILD",
        sha256 = LLVM_SHA256,
        strip_prefix = "llvm-project-" + LLVM_COMMIT,
        urls = [
            "https://storage.googleapis.com/mirror.tensorflow.org/github.com/llvm/llvm-project/archive/{commit}.tar.gz".format(commit = LLVM_COMMIT),
            "https://github.com/llvm/llvm-project/archive/{commit}.tar.gz".format(commit = LLVM_COMMIT),
        ],
    )
