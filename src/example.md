# Ablauf eines Fuzzing Prozesses
Ein Beispiel wie der Ablauf der Übung in etwa aussehen soll. Das Beispiel behandelt Übung 2 aber ist für alle weiteren ebefalls anwendbar.

1. Mount prüfen  
Prüfe ob der Ordner richtig im Contanier gemountet wurde.
```bash
ls / | grep fuzz
```

2. Compilieren des Zieles
In den Übungen ist dieser Schritt schon erfolgt!
```bash
afl-c++ /fuzz/target/server_v1.c++ -o /fuzz/target/server_v1.out
```

3. Programm testen  
Schaue in der `corpus/` Directory nach wie der Input für den Server aussieht.
```bash
# Input nachschlagen
cat /fuzz/corpus/v1/input.txt

# Binary ausführen
/fuzz/target/sever_v1.out /fuzz/corpus/v1/input.txt
```

4. Bearbeiten und testen  
Bearbeite die Input Datei im Editor und probiere verschiedene Eingaben.
Schaffst du es die Flag zu erlangen?

5. Mutator schreiben  
Sobald die Flag händisch gefunden wurde ist es das Ziel einen Mutator zu schreiben, welcher die Flag selbstsändig findet.
Greife hierzu auf die Docs von AFLplusplus zurück, die Mutator Docs findest du [hier](https://github.com/AFLplusplus/AFLplusplus/blob/stable/docs/custom_mutators.md).

    Um die Lauffähigkeit/Funktion des Mutators zu testen kann das `test_mutator.py` Skript verwendet werden. Als einzigen Parameter erhält es die Nummer der Version und stellt 10 Eingaben des Fuzzers im Terminal aus.

6. Fuzzer starten
Der Fuzzer kann mit dem Mutator gestartet werden um die "Schwachstelle" zu finden.

```bash
# nur Eingaben des Mutators verwenden
export AFL_CUSTOM_MUTATOR_ONLY=1

export PYTHONPATH="/fuzz/mutator/"
export AFL_PYTHON_MODULE="mutator_v1"

afl-fuzz -i /fuzz/corpus/v1/ -o /fuzz/finding/ -S server_v1 -- /fuzz/target/server_v1.out @@
```
