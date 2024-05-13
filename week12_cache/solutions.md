# 3.1.1
a[0][0]: 0x0000'0000
a[0][1]: 0x0000'0001
a[0][2]: 0x0000'0002
a[0][9]: 0x0000'0009
a[1][0]: 0x0000'000A
a[1][1]: 0x0000'000B
a[4][9]: 0x0000'0031

b[0][0]: 0x0000'0032
b[4][9]: 0x0000'0063

c[0][0]: 0x0000'0064
c[4][9]: 0x0000'0095

# 3.1.2
RAM Size: 
uint8_t für valid
uint32_t für tag
pro Zeile 4 Bytes nutzdaten + uint8 + uint32 = 9 Bytes pro Zeile
Totale grösse: 4 Zeilen * 9 Bytes = 36 Bytes

Grösse Cache Total: 36 Bytes
Zeilen: i = 2 -> 2^2 = 4 Zeilen
Grösse Zeile: o = 2 -> 2^2 = 4 Bytes Nutzdaten
Grösse Cache Nutzdaten: 16 Bytes
 
Anzahl der Indexbits bestimmt Anzahl Zeilen im Cache
Anzahl der Offsetbits bestimmt Anzahl Bytes in einer Cache Zeile
Index einer Memory...
Tag zeigt, welcher....

# 3.2
## Functions 
void init_cache(void) // initializes cache with default values
result_t access_cache(uint32_t address) // tries to read from cache -> if miss fetch value and store in cache
## Unterschied
Keine direkten zugriffe auf die Speicher addressen
## Wanum Unterschied
Weil sonst der cache nicht verwendet werden würde

## Simulation
Anzahl Hits: 0
Anzahl Misses: 150
Hit-Rate: 0%
Miss-Rate: 100%

## Tabelle
b[0][0], 0x32, miss, Zeile 0
c[0][0], 0x64, miss, Zeile 1
a[0][0], 0x00, miss, Zeile 0
b[1][0], 0x3C, miss, Zeile 3
c[1][0], 0x6E, miss, Zeile 3
a[1][0], 0x0A, miss, Zeile 2
b[2][0], 0x46, miss, Zeile 1

# 3.3 Schleifen Optimierung
Optmierung: Zuerst über die Columns und dann über die Rows Iteriert

Erster Hit bei Adresse: 0x65
Anzahl Hits: 37
Anzahl Misses: 113
Hit-Rate: 25%
Miss-Rate: 75%

# 3.4 Cache Optimierung
Offset: 4
Index: 2
Anzahl Hits: 120
Anzahl Misses: 30

Grösse Cache: 16 Bytes * 4 Bytes = 64 Bytes
Ca 1 zu 3

# 3.5 Grosses Array
Mit Änderungen
Anzahl Hits: 1125
Anzahl Misses: 375
Hit-Rate: 75%
Miss-Rate: 25%

Ohne Änderungen
Anzahl Hits: 0
Anzahl Misses: 1500
Hit-Rate: 0%
Miss-Rate: 100%