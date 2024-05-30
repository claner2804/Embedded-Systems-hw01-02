Aufgabe 1.2 "High-Level" Bibliothek für die Verwendung des Joysticks (20%)
Für zukünftige Aufgaben wollen wir einen Gerätetreiber (da es ja auf unserem Mikrocontroller kein Betriebssystem gibt, das die Ansteuerung der Hardware für uns übernimmt, müssen wir direkt Gerätetreiber in unseren Programmen einbinden) für den auf den EduArdu verbauten Joystick implementieren. Der Joystick besitzt neben der x- und der y-Achse auch einen Button, d.h. der Joystick selber kann auch wie ein Knopf gedrückt werden.
Der Gerätetreiber für den Joystick soll die Form einer Klasse haben, die die interne Ansteuerung des Joystick kapselt und eine einfach zu verwendende öffentliche Schnittstelle zur Verfügung stellt.
Öffentliches Interface
Diese Klasse soll JoystickHigh heißen und folgende öffentliche Schnittstelle besitzen:
	• JoystickHigh(int pinX, int pinY, int pinButton): Dem Konstruktor sollen die Pinnummern übergeben werden, an denen die analogen Axen des Joysticks und der Button angeschlossen sind.
	• void begin(): Initialisiert den Gerätetreiber. Wird einmalig zu Beginn des Mikrocontroller-Programms ausgeführt.
	• void update(): Liest die aktuellen Werte der Joystick-Achsen und des Buttons aus und speichert diese zwischen.
	• int16_t getPosX(bool immediate = false): Gibt die aktuelle Position der x-Achse zurück. Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
	• int16_t getPosY(bool immediate = false): Gibt die aktuelle Position der y-Achse zurück. Der mögliche Wertebereich soll von -512 (links) über 0 (Ruheposition) bis 512 (rechts) gehen.
	• bool getButton(bool immediate = false): Gibt den aktuellen Status des Buttons zurück. Rückgabewert ist true, wenn der Button gerade gedrückt ist, ansonsten false.
	• void setDeadzone(int16_t deadzone): Erlaubt es, die Deadzone des Joysticks einzustellen.
	• int16_t getDeadzone(): Gibt die aktuell eingestellte Deadzone zurück.
Sie können dieses Interface noch durch eigene Methoden ergänzen.
Implementieren Sie den Gerätetreiber in den Dateien JoystickHigh.h bzw. JoystickHigh.cpp.
update() und die immediate Eingabeparameter
Wenn in einem Mikrocontroller-Programm der Joystick verwendet wird, dann gibt es klassischerweise eine Endlosschleife im Programm (die sog. Event-Loop), in der der aktuelle Status des Joysticks in regelmäßigen Abständen abgefragt wird.
Dabei will man normalerweise nicht, dass sich ein Wert (z.B. die Position der x-Achse) innerhalb derselben Iteration dieser Event-Loop ändert, sondern dass die Werte gleich bleiben. Deswegen wird oft gleich zu Beginn einer Iteration der Event-Loop die aktuellen Werte ausgelesen, in Variablen zwischengespeichert und im weiteren Code aussschließlich die zwischengespeicherten Werte verwendet.
In unserem Gerätetreiber ist es die Aufgabe der Objektfunktion update(), dass die aktuellen Werte ausgelesen und in Objektvariablen zwischengespeichert werden.
Wenn die Funktionen getPosX(), getPosY() bzw. getButton() aufgerufen werden, dann kann anhand des Eingabeparameters immediate bestimmt werden, ob der von update() zwischengespeicherte Wert zurückgegeben wird (immediate ist false), oder der gerade aktuelle Wert frisch ausgelesen wird (immediate ist true).
Deadzone
Der Joystick weißt gewisse Fertigungstoleranzen auf, was dazu führen kann, dass der Joystick nicht immer genau in der Mitte zur Ruhe kommt und es zu unbeabsichtigten Joystick-Bewegungen kommen kann. Damit das keine Probleme verursacht, wird eine sog. "Deadzone" verwendet.
Implementierung
Für die Implementierung dieses Gerätetreibers verwenden wir die von Arduino bereitgestellte High-Level Bibliothek (Deshab das Postfix High im Klassennamen).
Für die Implementierung interessante Funktionen der Arduino Bibliothek sind:
	• analogRead()
	• map()
Für das Debugging können Sie das Serial Objekt verwenden. Dieses repräsentiert den von der Arduino Programmbibliothek bereitgestellten Gerätetreiber für die serielle Schnittstelle:
	• Serial.begin(int speed): Initialisiert die serielle Schnittstelle mit der angegebenen Geschwindigkeit.
	• Serial.print(value): Gibt den angegeben Wert über die serielle Schnittstelle aus. value kann ein String, eine Ganzzahl oder eine Gleitkommazahl sein.
	• Serial.println(value): Wie Serial.print(), nur dass am Ende noch ein Zeilenumbruch mit ausgegeben wird.
Der Mikrocontroller-Pin, an dem der Joystick-Button hängt, kann leider nicht über die Arduino Bibliothek angesprochen werden. Daher können Sie für diesen nicht die Arduino High-Level Bibliothek verwenden, sondern Sie müssen ihn direkt über die entsprechenden Register konfigurieren und auslesen.
Demo
Schreiben Sie ausserdem ein kleines Programm (in der Datei main.cpp), das die Verwendung ihres Gerätetreibers demonstriert.


![image](https://github.com/claner2804/Embedded-Systems-hw01-02/assets/131294860/ee53162e-177f-446c-91e7-804121a9ee16)
