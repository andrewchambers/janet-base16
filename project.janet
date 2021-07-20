(declare-project
  :name "base16"
  :description "Base 16 encoding/decoding of buffers."
  :author "Andrew Chambers"
  :license "MIT"
  :url "https://github.com/andrewchambers/janet-base16"
  :repo "git+https://github.com/andrewchambers/janet-base16.git")


(declare-native
  :name "base16"
  :source ["base16.c"])
