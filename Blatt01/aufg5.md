### 1. x = (float)7/4;
Cast zu float nötig, da es sich sonst um eine Integer-Division handelt. (Integer-Division => Keine Nachkommastellen)

### 2. x = (double)(7/(float)4);
- Casten zu double unnötig, da Division bereits eine Floatingpointnumber ergibt
- Casten zu float nötig, da sonst eine Integer-Division entsteht.

### 3. x = (double)(7/4.0);
- Casten zu double nicht nötig, da bereits eine Floatingpointnumber bei der Division entsteht.

### 4. x = (double)(7/4);
- Das casten hier ist nicht notwendig, da es sich nicht auf den Wert des Ergebnises der Division auswirkt

### 5. x = (double)7/4;
- Das casten hier wirkt sich auf die Division aus. Es wird eine Floatingpointnumber entstehen.

### 6. x = (double)7.0f/4;
- Dreifachgemoppelt. Wir haben hier 3 mal eine vorgabe eines Zahlentyps. Einer reicht allerdings, um keine Integer-Division zu erhalten.
    - (double)7/4 = 1.750000
    - 7.0f/4 = 1.750000
    - 7.0/4 = 1.750000
    - ~~7/4 = 1~~