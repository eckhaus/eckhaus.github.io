Databázy
=========

### Zdroje na preskúmanie

* [Binding MOAD](http://www.bindingmoad.org/)
* [LigASite](http://www.ligasite.org/)
* [Catalytic Site Atlas (CSA)](http://www.ebi.ac.uk/thornton-srv/databases/CSA/)
* [PDBe PISA, PDBe Fold, PDBe](http://www.ebi.ac.uk/pdbe/node/1)
* [RCSB PDB](http://www.rcsb.org/pdb/home/home.do)
* [Uniprot (Swissprot+spol.)](http://www.uniprot.org/)
* [Interpro](https://www.ebi.ac.uk/interpro/)
* [Enzyme portal](http://www.ebi.ac.uk/enzymeportal/)
* [FireDB](http://firedb.bioinfo.cnio.es)
* [PDBsite](http://wwwmgs.bionet.nsc.ru/mgs/gnw/pdbsite/)
* [BindingDB](https://www.bindingdb.org/bind/index.jsp)
* [Merops](https://merops.sanger.ac.uk/index.shtml)
* [EBI Intact](http://www.ebi.ac.uk/intact/)
* [String DB](http://string-db.org/)
* [CATH](http://www.cathdb.info/)

* [Expasy](http://www.expasy.org/)
* [ebi.ac.uk](www.ebi.ac.uk)
* [BioMart: Martservice](http://www.biomart.org/martservice.html)

### Dátové formáty

* [Protein Data Bank format (PDB)](http://pdb101.rcsb.org/learn/guide-to-understanding-pdb-data/introduction)
* [Simplified molecular-input line-entry system (SMILES)](http://www.daylight.com/dayhtml/doc/theory/)
* [PDBx/mmCIF - formát ktorý má od 2016 nahradiť PDB](http://mmcif.wwpdb.org/docs/faqs/pdbx-mmcif-faq-general.html)

### Preskúmať

* Protein docking

### [D01] [D01] Binding MOAD

*Michigan University, 2004*

Jedna z najväčších databáz svojho druhu. Obsahuje údaje o protein-ligand(-cofactor) interakciách s malými biologicky aktívnymi molekulami (t.j. nie protein-protein interakcie). Ide o výcuc z PDB, manuálne vyberaný a kontrolovaný. Najzaujimavejšia vlastnosť tejto databázy je asi objem (tiež ručne zozbieraných) údajov o väzobnej [afinite] [D01c].

> Väzobná afinita (binding affinity) je niečo úplne iné ako samotná účinnosť ligandu ("ligand efficacy")... afinita však obecne vyjadruje niečo ako mieru intermolekulárnych síl, teda urýchľuje reakcie a v našom prípade hovorí o lepšom "zapadnutí" ligandu. 

**Čo je v databáze:**

 * (ručne anotované) interakcie s malými biologicky aktívnymi molekulami
 * data o afinite z krystalografických článkov

**Druhy väzieb:**

 * Protein - ligand
 * Protein - cofactor
 * Protein - ligand - cofactor

V databáze sa dá vyhľadávať online, nie ale je možné po sieti pristupovať do databázy priamo. Dostupné je však RESTful-ish rozhranie pre sťahovanie dát v csv/zip. Pre dané PDB poskytuje možnosť stiahnuť si buď upravený PDB file proteínu (odstránenými atómami viac ako 10 Angstrom o proteínu), zoznam podobných proteínov (viď vpravo) alebo zoznam všetkých proteínov (v databáze) triedy do ktorej patrí ( podľa [EC number](https://en.wikipedia.org/wiki/Enzyme_Commission_number)).

> **Ligand may be:**

> * peptide of 10 amino acids or less
> * oligonucleotide of 4 nucleotides or less
> * small organic molecule (e.g. ibuprofen)
> * cofactor (e.g. NADPH)

**Príklad zoznamu:**

Napravo máme EC triedu *3.4.21.7*, ktorá obsahuje jednu rodinu proteínov s reprezentatnom 1CEB (PDB) a jedným ďalším proteínom 1CEA. Po názve proteínu vždy nasledujú prvky vstupujúce do reakcie (s popisokom valid/invalid). Jednotlivé stĺpce sú presne popísané na stránkach [MOAD FAQ](http://www.bindingmoad.org/Home/faq) pod "What is the CSV format?".

```
3.4.21.7,,,,,,,,,
,Family. Representative Entry is ,1CEB,,,,,,,
,,,AMH:A:90,valid,Ki,~,1,uM,C1CC(CCC1CN)C(=O)O,
,,,AMH:B:90,valid,Ki,~,1,uM,C1CC(CCC1CN)C(=O)O,
,,1CEA,,,,,,,
,,,ACA:A:90,valid,Kd,~,11,uM,C(CCC(=O)O)CCN,
,,,ACA:B:90,valid,Kd,~,11,uM,C(CCC(=O)O)CCN,
```


 Webové rozhranie pre `PDB=10GS, EC=2.5.1.18`:
`www.bindingmoad.org/Pdbrecords/download/CSV/10gs.csv`
`www.bindingmoad.org/Pdbrecords/download/CSV/family385.csv`
`www.bindingmoad.org/Pdbrecords/download/CSV/class_2.5.1.18.csv`

> Z [hlavného článku o MOAD] [D01a]: "Homologous protein families in each EC class are created using the comparison matrix generated from step 1 *pozn. (BLAST)*. At this stage, two entries (A and B in a class) are grouped together into a homologous family if one of the sequences in A is ≥ 90% identical to one of the sequences in B."

**Referencie**

[1) L Hu, ML Benson, RD Smith, MG Lerner, HA Carlson. Binding MOAD (Mother Of All Databases).Proteins 2005, 60, 333-40.] [D01a]

[2) A. Ahmed, RD Smith, JJ Clark, JB Dunbar, HA Carlson. Recent improvements to Binding MOAD: a resource for proteinligand binding affinities and structures. Nucl. Acids Res. 2014, 43, D465-D469.] [D01b]

[WWW >] [D01]


[D01]: http://www.bindingmoad.org/
[D01a]: http://onlinelibrary.wiley.com/doi/10.1002/prot.20512/full
[D01b]: http://nar.oxfordjournals.org/content/43/D1/D465.fullhttp://nar.oxfordjournals.org/content/43/D1/D465.full
[D01c]: https://en.wikipedia.org/wiki/Ligand_(biochemistry)#Receptor.2Fligand_binding_affinity

### [D02] [D02] LigASite

*Universite de Lille, UCL*

O niečo menšia databáza ako MOAD. Pracuje na prakticky komplementárnych prípadoch (ešte preveriť). LigASite predpokladá, že väčšina biologicky irelevantných ligandov (nejakých náhodných kontaminantov, ktoré sa primárne neviažu na dané miesto) bude spadať do kategórie malých molekúl (pod 10 "ťažkých" atómov - t.j. not vodík AFAIK). Ďalej boli vyselektované ligandy s určitým počtom medziatomických väzieb (vypočítané automaticky - Sobolev et al. :nástroj [LPC] [D02b]). Hranica bola stanovená podľa podielu relevantných interakcií v závislosti na počte väzieb na nejakej malej podmnožine. Pri 100+ väzbách bolo len cca 10% väzieb irelevantných (čo sa môže hodiť aj pri filtrovaní dát z iných zdrojov).

**Čo je v databáze**

 * holo- a apo- štruktúry 391 (816 redundantných) proteínov
 * len interakcie s dostatočne vysokým počtom interatomických väzieb
 * prísne, ale prevažne automaticky vyselektované data z PDB obohatené o metainformácie z ďalších nástrojov

**Výhody**

Táto databáza má už na prvý pohľad veľa vlastností výhodných pre náš projekt. Poskytuje zoznam viazaných (holo) aj neviazaných (apo) štruktúr. Ako trénovací vstup pre algoritmy predikujúce aktívne miesta chceme použiť neviazanú štruktúru a výsledok porovnať s databázou viazaných štruktúr. Na stránkach LigASite  je práve tento proces popísaný ako jedno z primárnych zamýšľaných použití dát. Celý proces priradzovania a filtrovania bound/unbound štruktúr je vykreslený vo [flowcharte na stránkach](http://www.ligasite.org/index.php?chart)
a popísaný v geniálnom hlavnom [článku] [D02a] projektu.

> "A dataset used to benchmark binding site prediction methods should ideally consist of proteins with one unbound structure to apply the prediction method, and at least one bound structure to derive the reference definitions of known binding sites. This is necessary to account for the fact that proteins can undergo structural changes upon binding, and that consequently, applying a binding site prediction method to a bound structure from which the ligand is deleted does not reproduce appropriately situations where the binding site location is truly unknown."


**Rozhranie**

Rozhranie je tiež priateľskejšie ako u MOADu. Pre každé PDB apo-štruktúry (neviazanej) sa dá stiahnuť XML (dostupné [schema] [D02c]) obsahujúce všetky holo-štruktúry, počty väzieb, atómov ligandu, chemickú štruktúru, PDB id, smiles kód... celá non-redundant DB má cca 100 MB, ide však prakticky len o skompilované data z PDB + ďalších online dostupných nástrojov. Existuje teda aj ultra-kompaktná kostra databázy o veľkosti $\approx$ 700 kB obsahujúca

* field 1: apo PDB ID
* field 2: residue type and position of binding site residue
* field 3: a hyphen-separated list of holo PDB ID's in which the residue is found in contact with a ligand.

Príklad (PDB=1a4u):

XML file `http://www.ligasite.org/v9.7/xml/1a4u_ligasite.xml`

Súradnice `http://www.ligasite.org/pqs/1a4u.pqs`

Apo-binding site `http://www.ligasite.org/pqs/1a4u.pqs`


#### TODO:

Pre istotu chcecknut metodologiu MOAD-u, naozaj sa jedná len o malé molekuly, alebo som si misinterpretoval ten cutoff vo vzdialenosti 10A?

Prehnať data PyMolom, zistiť čo presne vyjadrujú tie súradnice (asi aktívne miesta, prečo je tam však pqs prípona.. PISA woodoo?)

 * Suradnice su nabindovane na `<contact>` attribute z XML-ka a proste externe dopĺňajú 3D polohu?
 * Apo binding site proste hovori o priestorovych zmenach pri prechode z neviazanej do viazanej strukury?

Zistiť ako sú skladované tie residues v XML-ku (asi doštudovať PDB).

Zistiť ako kvartérna štruktúra ovplyvňuje aktívne miesta, v čom sa využíva PISA.

**Referencie**

[(1)	Dessailly BH, Lensink MF, Wodak SJ; LigASite: a database of biologically relevant binding sites in proteins with known apo-structures; Nucleic Acids Res. 2008;36(Database issue):D667-73.] [D02a]

[WWW >] [D02]
[D02]: http://www.ligasite.org/
[D02a]: http://www.ncbi.nlm.nih.gov/pmc/articles/PMC2238865/
[D02b]: http://bip.weizmann.ac.il/oca-bin/lpccsu/
[D02c]: http://www.ligasite.org/v9.7/ligasite.xsd


### wwPDB: PDBe

*EBI-EMBL*

#### wwPDB (WorldWide PDB)

Na začaiatok je dôležité poznamenať, že **PDBe** (Protein Data Bank in Europe), **PDBj** (Protein Data Bank Japan), **BMRB** (Biological Magnetic Resonance Data Bank) aj **RCSB** (Research Collaboratory for Structural Bioinformatics Protein Data Bank) sú súčasťou združenia wwPDB zjednocujúceho hlavné (experimentálne) svetové proteínové databázy. wwPDB vydáva nové identifikátory (PDB, mmcif) a zabezpečuje aby vo všetkých databázach boli dostupné rovnaké informácie (viď [FAQ](http://www.wwpdb.org/about/faq)). Nás teda bude zaujímať iba databázové rozhranie, ktoré jednotlivé organizácie sprístupňujú, keďže všetky údaje by mali byť rovnaké. Bližšie popíšeme európsku vetvu - PDBe.

#### PDBe

Tak ako všekty databázy wwPDB, je aj PDBe vybudovaná nad experimentálne nájdenými 3D štruktúrami proteínov. Tie sú uložené v PDB súboroch obsahujúcich geometriu proteínu (t.j. súradnice v 3D priestore), typy atómov, väzby, metainformácie (pôvod modelu, metóda merania, dátum experimentu,...) a ďalšie relevantné údaje. Každý model má od wwPDB pridelené unikátne 4-miestne alfanumerické PDBid. Modely môžu predstavovať aj rôzne komplexy alebo zlúčeniny. Práve z takýchto záznamov vieme zistiť, kde sa nachádzajú aktívne miesta proteínov. Najjednoduchší prístup by bol najprv nájsť všetky atómy mimo proteínu (tie by mali byť popísané ako `HETATM`?) a za aktívne miesta označiť ťažké atómy z proteínu do istej vzdialenosti, ktoré nie sú v kovalentnej väzbe z proteínom (to sa dá zistiť podľa dĺžky väzby).

Takto by sme sa síce mohli dostať k potrebným údajom o aktívnych miestach a však tie by pravdepodobne neboli príliš správne. Práve tento problém sa snažili riešiť vyššie spomínané databázy precíznym výberom najkvalitnejších záznamov z PDB. Pre testovacie dáta teda priamy výber z PDB robiť nebudeme, použijeme skôr zoznamy z niektorej "prečistenej" (golden standard) databázy. Po natrénovaní systému už budeme chcieť prijímať ako vstup aj proteíny mimo týchto špecifických zoznamov - teda skoro určite budeme musieť pristupovať do PDB. V istej fáze vývoja bude ale možno tiež zaujímavé pracovať so všetkými modelmi vyselektovaných proteínov (nie len s ideálnymi, ktoré prešli výberovým mechanizmom ako napr. u LigASit-u) a pozorovať ako sa bude meniť kvalita výsledkov. V takom prípade môžeme použiť anotačnú databázu ako Uniprot, z nej vybrať všetky PDB daného proteínu a z nich si skompilovať vlastnú databázu pravdepodobných aktívnych miest.

### Poznámky

S MOADom to bude možno dosť ťažké. U veľkého množstva experimentálne dokázaných štruktúr ukazuje kde sú aktívne miesta, ako sú dobré a pod. Museli by sme však nájsť podľa PDB materský proteín a vyselektovat z Uniprotu, alebo niečoho takého (všekty/nejaké) nenaviazané štruktúry, na ktorých sa spustia skúmané predikčné algoritmy.. to by nemusel byť príliš veľký problém, ak by boli také štruktúry dostupné (zdá sa, že stačí jedna ak je to X-ray s dobrým rozlíšením (pod 2.5A) teda aspoň podľa ligasite-u)

Postup: zoberiem MOAD ako zaručený štandard, vyťažím všetky Uniprot accession IDs obsahujúce daný PDB. Z Uniprot vytiahnem PDB všetkých štruktúr a cez RCSB/PDBe zistím, či je to len čistý proteín... čo teda nemusí byť také jednoduché, čistý nikdy nebude - ide pravdepodobne skôr o to či sú voľné miesta na ktorých predpovedá MOAD nejaké väzby? (a tiež, ako by boli definované voľné miesta - žiadne väzby v nejakom rádiuse?)

LigASite má toto všetko poriešené, nič netreba predspracovávať, vyhodnocovať. Jedine možno pridať anotácie o proteínovej skupine, ale to ide ľahko z Uniprotu/hocičoho.

Ďalej by sa dali informácie sťahovať priamo z nejakej veľkej databázy (čo sa v konečnom dôsledku budeme musieť, keď už budeme spúšťať systém "na ostro"). RCSB aj PDBe majú slušné webové rozhranie. Zoznamy ku konkrétnym proteínom sa dajú opäť zohnať z Uniprotu.

Ostáva preskúmať zdroje z EMBL/EBI + FireDB (čo je tiež z väčšej časti založené na CSA), a veľké anotačné databázy (Uniprot a asi InterPro)
