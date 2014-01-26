# Code generation
configure_file(codegen.cmake.in codegen.cmake @ONLY)
configure_file(initgen.cmake.in initgen.cmake @ONLY)

# Exports
configure_file(defgen.cmake.in defgen.cmake @ONLY)
configure_file(symgen.cmake.in symgen.cmake @ONLY)
