# Protokoll Fuzzing - Übung

## Installation
Für diese Übung werden folgende Tools benötigt:
- Docker
- Editor (VSC emfpohlen)

Die Installtion kann mif folgden Commands erfolgen:
```bash
# install docker
sudo apt install docker.io

# install VSC
sudo apt install code

# add your user to the docker group
sudo usermod -aG docker $(whoami)

# reboot your system to apply changes
sudo reboot now
```

Als nächstes muss der Docker Container heruntergeladen werden und kann danach ausfegührt werden. Da der Ordner dieser Übung in den Container gemountet wird müssen die Behehle in Ordner `Fuzz/` ausgeführt werden.
```bash
# download the container
docker pull aflplusplus/aflplusplus

# run the container
docker run -ti -v $PWD:/fuzz aflplusplus/aflplusplus
```

Es kann nun auf alle Dateien dieser Übung im Container über den Pfad `/fuzz/` zugegriffen werden. Änderungen außerhalb des Containers sind innerhalb enbenfalls ersichtlich also können die Dateien außerhalb des Container mit dem Editor der Wahl (VSC, vim, ...) geändert werden.

## Mutators
Um lediglich die Mutationen aus dem Script zu verwenden muss diese Option aktiviert werden.
```bash
export AFL_CUSTOM_MUTATOR_ONLY=1
```

Um die selber geschriebenen Mutator zu finden muss die direcotry zu diesen in die Python Path Variable hinzugefügt werden und das Modul für den Fuzzingvorgang gesetzt werden.
```bash
# update the python path
export PYTHONPATH="/fuzz/mutators/"

# select the module you want to use (the name of the script without .py)
export AFL_PYTHON_MODULE="mutator_v1"
```

> Note: Wenn ein anderer Mutator benötigt wird muss der zweite Command erneut mit dem andern Modulnamen ausgeführt werden.

## Fuzzing
> Bei folgenden Commands müssen überall Änderungen gemacht werden wo eckige Klammern auftauschen! `<change_me>`

Bevor der Fuzzer ausgeführt werden kann muss das Target zunächst Instrumentalisiert werden. Für dies wird der AFL Compiler werwendet, welcher sich für C++ `afl-c++` nennt. Die  Standardparameter reichen uns für unsere Einsatzzwecke aus also kann er wie der normale GCC
Compiler verwendet werden.

```bash
afl-c++ /fuzz/target/server_<version>.cpp -o /fuzz/target/server_<version>.out
```

Um den Fuzzer zu starten wird der Command `afl-fuzz` ausgeführt, dieser wird zusätzlich zu den übergebenen Parameter mit den gesetzten Umgebungsvariaben konfiguriert also ist darauf zu achen ob auch die richtigen gesetzt sind. Die gesetzten Variablen werden beim Starten des Fuzzers angezeigt für mehr Informationen siehe `afl-fuzz -hh`.

```bash
afl-fuzz -i /fuzz/corpus/<dirname> -o /fuzz/finding/ -S server_<version> -- /fuzz/targets/server_<version>.out @@
```

### Überwachung
Will man die EIngaben des Fuzzers während des Fuzzing Vorgngs sehen kann dies in einem zweiten Terminal geschehen. 
Zunächst muss eine neue Eingabeaufforderung auf dem Container gestartet werden.
```bash
# get the container id (first hexadecimal value)
docker container ls

# get a bash on the container
docker exec -it <container_id> /bin/bash
```

Die aktuelle Eingabe des Fuzzers befindet sich in einem versteckten file in der `/finding/<version>` Directory. Der Befehl `watch` kann verwendet werden um die Datei zyklisch auszulesen.
```bash
watch -n 0.1 cat /fuzz/finding/server_<version>/.cur_input
```

> Die `-n` Flag kann verwendet werden um die Abstände der Zeitintervalle in Sekunden festzulegen. 

## Nützlichen Environment Variablen
In den Standardeinstellungen wird beim Starten von `afl-fuzz` die Ausgabe des Programmes unterdrückt und die Fuzzing-UI gestartet.
Für den Debugging Prozess kann es jedoch sinvoll sein die Ausgaben zu sehen um z.B. festzustellen ob Parameter richtig eingelesen werden.
```bash
# to enable debug mode use this command
export AFL_DEBUG=1 && export AFL_NO_UI=1

# to switch back to the GUI use
unset AFL_DEBUG && unset AFL_NO_UI
```