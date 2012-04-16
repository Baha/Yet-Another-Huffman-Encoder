for i in `ls tests/`; do
  ./modulo3 tests/$i
  ./modulo4 tests/$i".huf" tests/$i".txt"
  diff tests/$i tests/$i".txt"
done
rm tests/*.txt
rm tests/*.huf

# si al ejecutar el script, sale algun mensaje, la
# prueba ha fallado
