Interpreter jazyka Chef
=======================

Jazyk Chef je ezoterický programovací jazyk, v ktorom majú programy formu kuchárskych receptov. Chef bol navrhnutý Davidom Morgan-Marom v roku 2002 a existujú pre neho interpretery v jazykoch Perl a Python. V tomto projekte sme implementovali interpreter chefu v jazyku C++.

## Jazyk

Programy v jazyku Chef sú prezentované vo forme kuchárskych receptov, kde ingrediencie predstavujú premenné, jednotlivé pokyny v postupe sú príkazmi a nádoby (miska - mixing bowl a plech - bakeware) slúžia ako zásobníky čísel (teda pamäť).


Štrukturálne sa každá metóda (recept) jazyka skadá z 3 častí:

* Hlavička - obsahuje názov a popis receptu
* Ingrediencie - popisujú premenné
* Metóda receptu - príkazy receptu

Program sa môže skladať z viacerých podreceptov. Na začiatku behu sa spustí hlavný recept (prvý v poradí) a ostatné recepty sa chovajú ako procedúry, ktoré je možné hocikedy z programu zavolať.

### Hlavička

Každý recept (procedúra) sa začína názvom. Názov je prvý riadok receptu ukončený bodkou a môže obsahovať ľubovoľné znaky ASCII, vrátane medzier. Po ňom nasledujú nepovinné komentáre popisujúce beh programu. Komentáre môžu byť aj viacriadkové. Ich koniec určuje riadok "Ingredients." označujúci začiatok sekcie ingrediencií.



*Príklad hlavičky:*
```
Fibonacci Numbers.

This recipe prints the first 100 Fibonacci numbers. It uses an auxiliary recipe for caramel sauce to define Fibonacci numbers recursively. This results in an awful lot of caramel sauce! Definitely one for the sweet-tooths.
```

### Ingrediencie

Blok popisujúci ingrediencie (premenné) sa začína riadkom "Ingredients.". Každá ingrediencia ja zapísaná na novom riadku a obsahuje tieto parametre:

* Názov - podľa neho identifikujeme premennú
* Hodnota - počiatočná hodnota premennej
* Merná jednotka - určuje o aký typ premennej sa jedná (číslo alebo znak)

Názov môže byť ľubovoľný zmysluplný alfanumerický reťazec (nemal by hlavne obsahovať názvy príkazov, môže však obashovať medzeru).
Hodnota je celé číslo popisujúce počiatočný stav ingrediencie. Merná jednotka je reťazec určujúci, či premenná predsatvuje číslo alebo znak.

Možné merné jednotky sú:

g, kg, pinch[es] : Číselné premenné
ml, l, dash[es] : Znakové premenné (ASCII)
cup[s], teaspoon[s], tablespoon[s] : Podľa pôvodnej špecifikácie jazyka môžu byť buď číselné alebo znakové. V našom interpretery ich defaultne berieme ako číselné premenné, keďže Chef obsahuje príkaz, ktorým vieme previesť premennú na znakovú, ale neexistuje spôsob ako takúto operáciu neskôr zvrátiť. Modifikátory (heaped a level) špecifikujú takéto premenné ako číselné, to však v programe nerobí žiaden rozdiel.

Za ingredienciami môžu nasledovať informácie o dĺžke prípravy receptu a teplote pece, ktoré však nemajú dopad na beh programu a preto sú pri parsovaní úplne ignorované.

### Vlastný recept

Pred tým, ako popíšeme syntax samotných príkazov objasníme, ako funguje pamäť v jazyku Chef. Každý recept obsahuje predom deklarovnané premenné - už spomínané ingrediencie. Okrem nich sa v každom recept používajú pomocné zásobníky označované ako "mixing bowls" (pamäť programu) a "baking dishes" (výstupný zásobník). Počas behu programu sa do zásobníkov vkladajú premenné, modifikuje sa ich obsah a zmenené hodnoty sa dajú opäť uložiť späť do premennej. Po skončení hlavného programu sa na výstup vypíše obsah nikoľko prvých "baking dishes" (teda výstupných zásobníkov).


Začiatok sekcie receptu obsahujúcej príkazy označuje riadok "Method."
Nasledujú príkazy, každý na samostatnom riadku, zakončený bodkou.

**Príkazy**
Nepovinné časti príkazov budeme uzatvárať do hranatých zátvoriek. Ak nie je uvedené, s ktorou nádobou (mixing bowl/baking dish) sa pracuje, budeme predpokladať, že ide o prvú nádobu (svojho druhu).
Argumenty príkazov určujúce poradie (o koľkú nádobu sa jedná) sú zapísané v tvare 1st, 2nd, 3rd, 4th ...

* *Take **ingredient** from refrigerator.* <br>
    Načíta číslo zo štandardného vstupu do premennej **ingredient**
    
    
* *Put **ingredient** into [nth] mixing bowl. * <br>
    Uloží hodnotu ingrediencie na vrch n-tého zásobníku.
    
    
* *Fold **ingredient** into [nth] mixing bowl. * <br>
    Odstráni hodnotu z vrchu n-tého zásobník a uloží ju do danej ingrediencie.
    
    
* *Add **ingredient** [to [nth] mixing bowl]. * <br>
    Pripočíta hodnotu ingredienci k hodnote na vrchu zásobníku.
    
    
* *Remove **ingredient** [from [nth] mixing bowl]. * <br>
    Pripočíta hodnotu ingredienci od hodnoty na vrchu zásobníku.


* Combine **ingredient** [into [nth] mixing bowl]. <br>
    Prenásobí hodnotu na vrchu zásobníku hodnotou ingrediencie.


* Divide **ingredient** [into [nth] mixing bowl]. <br>
    Predelí hodnotu na vrchu zásobníku hodnotou ingrediencie.
    

* Add dry **ingredients** [to [nth] mixing bowl]. <br>
    Pridá súčet hodnôt všetkých číselných ingrediencií na vrch zásobníku.


* Liquify **ingredient**. <br>
    Skonvertuje ingredienciu na znakový typ.
    
    
* Liquify contents of the [nth] mixing bowl.
    Skonvertuje všetky položky v zásobníku na znakový typ.
    

* Stir [the [nth] mixing bowl] for **number** minutes.
    "Potlačí" vrchnú položku zásobníka **number** miest hlbšie. Všetky ingrediencie, ktoré sa dostali nad neho sa tým pádom posunú o miesto vyššie.
    
    
* Stir **ingredient** into the [nth] mixing bowl.
    Na vrch zásobníku vloží ingredienciu a zavolá príkaz stir uvedený vyššie.
    
    
* Mix [the [nth] mixing bowl] well.
    Náhodne zamieša položky zásobníku.
    
    
* Clean [nth] mixing bowl.
    Vyprázdní zásobník
    
    
* Pour contents of the [nth] mixing bowl into the [pth] baking dish.
    Pridá obsah n-tého zásobníka na koniec p-teho výstupného zásobníka.
    
    
* **Verb** the **ingredient**.
    Táto konštrukcia označuje začiatok "while-cyklu", ktorý musí byť ukončený nižšie popísaným príkazom. **Verb** je identifikátorom cyklu. **ingredient** určuje podmienku. Ak je hodnota v **ingredient** nenulová, telo cyklu prebehne, inak sa vykoná skok za ukončovací príkaz cyklu.
    
    
* **Another verb** [the **ingredient**] until **verbed**.
    Ukončuje cyklus s identifikátorom **verb** (tj. **verbed** bez prípony ed). Pri každom vykonaní sa zníži hodnota v **ingredient** (ak je definovaná) o 1.
    
    
* Set aside.
    Ukončí vykonávanie inštrukcií najvnútornejšieho cyklu, program pokračuje za príkazom until.
    

* Serve with **auxiliary-recipe**.
    Zavolá pomocnú metódu. (viď. Pomocné recepty nižšie)
    

* Refrigerate [for **number** hours].
    Okamžite ukončí beh receptu. Ak ide o hlavný recept, vypíše sa na výstup **number** prvých výstupných zásobníkov. V prípade pomocného receptu sa len preskočia zvyšné príkazy a dáta sa predajú ďalej bežným spôsobom (viď. Pomocné recepty nižšie).
    
    
*  Serves **number-of-diners**.
    Určuje koľko výstupných zásobníkov sa má vypísať na výstup.
    
    
#### Pomocné recepty
Pomocné recepty slúžia ako funkcie jazyka Chef. Správajú sa vcelku podobne ako hlavný recept až na inicializáciu zásobníkov a predávanie výstupu.
    
Pomocný recept môžeme zavolať pomocou príkazu *serve with*. Pomocný recept si okopíruje všetky zásobníky z rodičovského receptu a začne vykonávať svoj kód v prostredí oddelenom od rodičovského procesu. Po spracovaní všetkých príkazov sa obsah prvého zásobníka pridá na koniec prvého zásobníka rodičovského receptu. Prázdny pomocný program teda napríklad len zduplikoval obsah prvého zásobíka rodičovského receptu.


### Príklad receptu

    1.   Fibonacci numbers.
    
    2.   This recipe calculates fibonacci numbers.
    
    3.   Ingredients.
    4.   0 g fib1
    5.   1 g fib2
    6.   16 g iterator
    7.   16 g second iterator
    
    8.   Method.
    9.   Chop iterator.
    10.  Put fib2 into 1st mixing bowl.
    11.  Put fib2 into 1st mixing bowl.
    12.  Add fib1 into 1st mixing bowl.
    13.  Fold fib2 into 1st mixing bowl.
    14.  Fold fib1 into 1st mixing bowl.
    15.  Put fib1 into 1st mixing bowl.
    16.  Chop iterator until choped.
    17.  Mash second iterator.
    18.  Fold fib1 into 1st mixing bowl.
    19.  Put fib1 into 2nd mixing bowl.
    20.  Mash second iterator until mashed.
    21.  Pour contents of 2nd mixing bowl into the baking dish.
    
    22.  Serves 1.
    
 Program vypočíta prvých 16 Fibonacciho čísel.
 V riadku 1. je názov receptu. V 2. riadku komentár. V 3.-7. sú popísané premenné prgramu, všetky numerické.
 
 Od 8. riadku sa začína samotné telo programu.
 
 Chop iterator označuje začiatok cyklu "Chop", ktorý končí riadkom 16. (príkazom until chopped). Telo cyklu urobi krok výpočtu nasledovne: do zásobníka sa 2x načíta hodnota fib2 ($F_n$), potom sa k vrchu zásobníka pričíta fib1 ($F_{n-1}$), čím vznikne ďalší člen ($F_{n+1}$). Ten sa načíta do fib2 a zvyšná pôvodná hodnota fib2 sa načíta do fib1. Takto sme sa dostali zo stavu kde fib1 = $F_{n-1}$, fib2 = $F_n$ do stavu, kde fib1=$F_n$ a fib2 = $F_{n+1}$. Nakoniec ešte uložíme hodnotu fib1 na zásobník, kde zostane až do vypísania výsledku.
 
 Cyklus "Mash" na riadkoch 18. až 20. len prevráti poradie prvého zásobníku tak, že vždy načíta vrch zásobníka do premennej (18.) a následne uloží obsah premennej do druhého zásobníka.
 
 Riadok 21. presunie obsah zásobníku 2 (prevrátená postupnosť) do výstupného zásobníku a príkaz serve túto postupnosť vypíše na výstup.
 
 
 ## Interpreter
 
 Interpreter berie za vstup zdrojový kód programu. Ten môže byť načítaný buď zo štandardného vstupu, alebo zo súboru použitím prepínača "-i MenoSúboru". Výstupom je výpis z výstupných zásobníkov podľa príkazu "Serves", po prípade dodatočné informácie, ak bol pri spustení interpreteru zadaný prepínač -v (verbose). Dodatočné informácie zahŕňajú pre každý recept (aj pomocný) v zdrojovom kóde názov receptu, komentár, naparsované ingrediencie, príkazy a miesta skokov v programe. Toto uľahčuje debugging a zároveň poskytuje užívateľovi štruktúrovanú informáciu o spúšťanom skripte.
 
 Posledným prepínačom je "-t", ktorý zapína tracing - teda vykonávanie kódu krok po kroku. Po vykonaní každého príkazu čaká interpreter na pokyn od užívateľa (stlačenie enter) a vypíše stav pracovných zásobníkov práve spracovávaného receptu. Pri volaní (resp. ukončení spracovávania) pomocného receptu sa vypíše správa.
 
 ## Technické detaily
 
 V tejto časti popíšme beh interpreteru a metódy akými spracováva vstup. Rozhranie jednotlivých všetkých tried a metód tu však už nebudeme podrobnejšie rozoberať, keďže je zahrnuté v doxygen dokumentácii.
 
 ### Parsovanie
 
 Interpreter sa skladá z dvoch hlavných tried Program a Recipe. Trieda Program načíta vstup z súboru (resp. STDIN). Väčšina parsovania je realizovaná použitím regulárnych výrazov. Každý riadok sa prevedie na malé písmená, odstráni sa leading a trailing whitestpace, ako aj prebytočné opakujúce sa medzeri vo vnútri textom. Pre každý recept sa vytvorí nový objekt triedy Recept, ktorý obsahuje všetky potrebné informácie pre beh programu. Hlavný recept sa uloží priamo do atribútu Program::main_recipe, všetky vedľajšie recepty patria už pod tento hlavný recept (viď. nižšie). 
 
 Najskôr sa načíta hlavička (Program::LoadHeader). Prvý riadok ukončený bodkou sa považuje za názov programu. Zvyšok textu až po začiatok bloku ingrediencií je komentrár. 
 
 
 Ingrediencie sa parsujú (Program::LoadIngredients) pomerne jednoducho, keďže majú fixný formát hodnota-jednotka-názov. Jednotlivé položky sa opäť vyextrahujú regexpom a uložia do mapy ingrediencií receptu, kde kľúč je názov ingrediencie a hodnota je trieda Ingredient obsahujúca počiatočnú hodnotu, typ ingrediencie atď.
 
 Nasleduje spracovanie príkazov receptu (Program::LoadRecipe). Pre každý druh príkazu máme regexp, ktorý dokáže zo zdrojového kódu vybrať potrebné parametre. Všetky príkazy jazyka chef majú najviac dva argumenty, preto si môžeme pre každý takto naparsovaný príkaz zapamätať štruktúru (Command) s názvom príkazu a 2 argumentami. Načítané príkazy sa uložia do vektoru (Recipe::commands). Mierne odlišný prístup používame pre príkazy skoku.
 O každom skoku si vedieme záznam podľa jeho identifikátoru v mape (Recipe::jumps). Každý záznam obsahuje ID, začiatok skoku, koniec skoku, ingredienciu, ktorá tovrí podmienku pre skok a nepovinnú ingredienciu, ktorá sa dekrementuje pri vykonaní príkazu until.
 
 Po načítaní hlavného receptu sa načítajú všetky pomocné recepty, tie sa uložia do mapy pomocných receptov v hlavnom recepte. Každý recept má odkaz na hlavný recept (Recipe::parent).
 
 
 ### Beh programu
 
 Po naparsovaní zdrojového kódu máme v Programe načítaný hlavný recept, ktorý zas obsahuje všetky vedľajšie recepty. Všetky recepty majú načítané inštrukcie v formáte "príkaz+2 argumenty" uložené vo svojich vektoroch inštrukcií. Ingrediencie majú nastavené počiatočné hodnoty zo zdrojového kódu. Stačí nám teda začať vykonávať inštrukcie zaradom. Vykonávanie inštrukcií sa zabezprečuje každý recept sám. Začneme teda spustením hlavného receptu. Držíme si ukazateľ na poslednú vykonanú inštrukciu a v každom kroku vykonáme ďalšiu inštrukciu v poradí spustením príslučnej metódy. Ak dôjde k zavolaniu pomocného receptu, vytvoríme nový objekt typu Recept, do ktorého skopírujeme dáta príslušného pomocného receptu z hlavného receptu. 
 Následne sa skopírujú zásobníky (MixingBowls) z materského receptu do tohto nového receptu a ten sa spustí.
 Po ukončení behu pomocného receptu sa vloží jeho prvý zásobník na vrch materského receptu a pokračuje sa ďalej v behu materského receptu.
 
 Keď sa skončí výkon hlavného receptu, vypíšu sa výstupné zásobníky na výstup (t.j do súboru/ na STDOUT). To ktoré zásobníky sa vypíšu udáva premenné Recipe::serves nastavená príkazom "serves number-of-people" hlavného receptu.
 
 Implementácia väčšiny príkazov je priamočiara, keďže sa jedná hlavne o jednoduché operácie so zásobníkom. Jedine u cyklov si musíme pamätať "úroveň zanorenia", aby sme pri zavolaní príkazu Set aside (break). mohli rýchlo ukončiť vnútorný cyklus. To docielime tým, že vždy, keď vstúpime do cyklu, zapamätáme si ho v zásobníku skokov Recipe::jumpsStack a keď z neho vystúpime tak zmažeme posledný záznam. Pri zavolaní set aside nám stačí vziať posledný cyklus zo zásobníka a presunúť ukazateľ príkazov za koniec tohto cyklu.
 
 
 ## Aké súbory tento projekt obsahuje
 
 Samotný projekt sa dá nájsť na GitHub-e: https://github.com/eckhaus/eckhaus.github.io/tree/master/chef
 
 Skladá sa zo
 * zdrojového kódu v C++ - adresár source
 * dokumentácie (t.j. doxygen, web stránka a tento dokument - adresár docs
 * testovacích vstupov - adresar recipes.
 
 Dostupný je tiež Makefile, pre kompiláciu je však potrebný kompilátor C++ podporujúci knižnicu &lt;regex&gt; (napr. g++-5)
