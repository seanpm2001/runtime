"""Provides the repository macro to import LLVM."""

load("//third_party:repo.bzl", "tfrt_http_archive")

def repo(name):
    """Imports LLVM."""
    LLVM_COMMIT = "eb03fa1d2c05bad5a5f75a89d47b4b31d84bb90b"
    LLVM_SHA256 = "53260f7983218c72b07f905694505188695e94e4e68fb9f2959f89073724feac"

    tfrt_http_archive(
        name = name,
        sha256 = LLVM_SHA256,
        strip_prefix = "llvm-project-" + LLVM_COMMIT,
        urls = [
            "https://storage.googleapis.com/mirror.tensorflow.org/github.com/llvm/llvm-project/archive/{commit}.tar.gz".format(commit = LLVM_COMMIT),
            "https://github.com/llvm/llvm-project/archive/{commit}.tar.gz".format(commit = LLVM_COMMIT),
        ],
        link_files = {
            "//third_party/llvm:llvm.autogenerated.BUILD": "llvm/BUILD",
            "//third_party/mlir:BUILD": "mlir/BUILD",
            "//third_party/mlir:build_defs.bzl": "mlir/build_defs.bzl",
            "//third_party/mlir:linalggen.bzl": "mlir/linalggen.bzl",
            "//third_party/mlir:tblgen.bzl": "mlir/tblgen.bzl",
            "//third_party/mlir:test.BUILD": "mlir/test/BUILD",
        },
    )
