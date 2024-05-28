
DST_DIR="./depencyObj"

if [ ! -d "$DST_DIR" ]; then
    mkdir -p "$DST_DIR"
fi

cp ../Socket/*.{c,h} $DST_DIR