
# What's SEDEC?

Please refer to original <a href="https://github.com/tehokang/sedec-to-handle-any-section-of-mpeg-ts">SEDEC 1.0 </a>
At this moment, SEDEC is only for decoding and editting sections, not encoding.

# Architecture

SEDEC 2.0 has slightly different architecture from 1.0 so that 2.0 supports more tables of Hybridcast and MPEG-H.
Let's look at source tree, 'base' folder has base classes can be used by dvb, hybridcast and mpegh.
In other words, dvb, hybridcast and mpegh basically will have implementations to modify bases.

<code>
src 
├── base 
├── dvb
│   ├── descriptors
│   └── sections
├── hybridcast
│   ├── descriptors
│   └── sections
└── mpegh
    ├── descriptors
    └── sections
</code>


# How to build

SEDEC is built on cmake, c++ library has to support c++11.

<code>
$mkdir build
$cd build
$cmake -DCMAKE_TOOLCHAIN_FILE=../cmake/XXXXX.cmake (you can choose what you want)
$make
$make install
</code>

# How to run examples

Project has sections for example in sections-dumped and you can run executables after building
<code>
$./out/bin/sedec-dvb-decoder ../examples/sections-dumped/dvb/ait/XX_XXX_XXX
</code>

The presentation of result has sample screen like 1.0 version of sedec
