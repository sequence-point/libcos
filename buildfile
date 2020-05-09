./: {*/ -build/ -examples/ -docs/} doc{CHANGELOG LICENSE README} manifest

# Don't install tests.
#
tests/: install = false
