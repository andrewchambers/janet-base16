(import build/base16 :as base16)

(def rng (math/rng (os/time)))

(loop [i :range [0 10]]
  (def n (math/rng-int rng 16))
  (def buf (math/rng-buffer rng n))
  (def e1 (base16/encode buf))
  (def e2 (base16/encode buf (buffer/new n)))
  (unless (= e1 (string e2)) (error "expected same result"))
  (def d1 (base16/decode e1))
  (def d2 (base16/decode (string/ascii-upper e1)))
  (def d3 (base16/decode e1 (buffer/new n)))
  (unless (= 
            (string d1)
            (string d2)
            (string d3)
            (string buf))
    (error "expected same decode")))