Databázy
=========

### D001 Binding MOAD

*Michigan University, 2004*

Jedna z najväčších databáz svojho druhu. Obsahuje údaje o protein-ligand(-cofactor) interakciách s malými biologicky aktívnymi molekulami (t.j. nie protein-protein interakcie). Ide o výcuc z PDB databázy, manuálne vyberaný a kontrolovaný. Najväčšia "feature" tejto databázy je asi objem (tiež ručne zozbieraných) údajov o väzobnej [afinite](https://en.wikipedia.org/wiki/Ligand_(biochemistry\)#Receptor.2Fligand_binding_affinity).

> Väzobná afinita (binding affinity) je niečo úplne iné ako samotná účinnosť ligandu ("ligand efficacy")... afinita však obecne vyjadruje niečo ako mieru intermolekulárnych síl, teda urýchľuje reakcie a v našom prípade hovorí o lepšom "zapadnutí" ligandu. 

Čo je v databáze:

 * interakcie s malými biologicky aktívnymi molekulami
 * len manuálne pridané data z krystalografických článkov

Druhy väzieb

 * Protein - ligand
 * Protein - cofactor
 * Protein - ligand - cofactor

V databáze sa dá vyhľadávať online, nie je možné pristupovať do databázy priamo. Dostupné je však RESTful-ish rozhranie pre sťahovanie dát v csv/zip. Pre dané PDB poskytuje možnosť stiahnuť si buď PDB file proteínu (s interakciami), zoznam podobných proteínov alebo zoznam všetkých proteínov danej triedy ([EC number](https://en.wikipedia.org/wiki/Enzyme_Commission_number)) v databáze.

> Z (hlavného článku o MOAD)[D001a] "Homologous protein families in each EC class are created using the comparison matrix generated from step 1 *pozn. (BLAST)*. At this stage, two entries (A and B in a class) are grouped together into a homologous family if one of the sequences in A is ≥ 90% identical to one of the sequences in B. With 90% sequence identity being so strict for clustering, we always found that any additional chains in entries A and B were also 90% sequence identical."

[WWW >] [D001]

[0001]: http://www.bindingmoad.org/
[D001a]: http://onlinelibrary.wiley.com/doi/10.1002/prot.20512/full
