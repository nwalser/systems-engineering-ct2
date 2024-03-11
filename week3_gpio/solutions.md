# 4
## 1
GPIOB: reg_stm32f4xx.h zeile 236
MODER: reg_stm32f4xx.h zeile 195

## 2
#define GPIOB ((reg_gpio_t *) 0x40020400)
dieses makro gibt einen Pointer auf die gegeben adresse zurück, ab dieser adresse wird dann eine "interpretation" des gegebenen structs reg_gpio_t gelegt.

## 3
Enthält die Definitionen der Offsets der einzelnen Register, bezogen auf eine GPIO Guppe.

## 4
GPIOB->MODER = 0x00000280;
zur adresse GPIOB wird der relative offset des im stuctes enthaltenen symbol (MODER) aufaddiert, danach dereferenziert und auf den gegebenen wert gesetzt.

# 6
## 1
### a
Dunkel: PA0 (LED16)
Hell: PA1 (LED17)
Floating: PA2 (LED18)

### b
ja

### c
led 18 flakert bei kontakt mit jumper wires. die induzierte spannung im draht kann nur sehr schlecht über den messeingang (welcher optimalerweise einen wiederstand von unendlich ohm hat) abfliessen. Darum flakert der Eingang.

### 5

        |       PD  |       PU  |    NO
PP      | 0:0  1:1  | 0:0  1:1  | 0:0  1:1
OD      | 0:0  1:0  | 0:0  1:1  | 0:0  1:0
OD + PU | 0:0  1:0  | 0:0  1:1  | 0:0  1:1