Databázy
=========

### D001 Binding MOAD

*Michigan University, 2004*

Jedna z najväčších databáz svojho druhu. Obsahuje údaje o protein-ligand(-cofactor) interakciách s malými biologicky aktívnymi molekulami (t.j. nie protein-protein interakcie). Ide o výcuc z PDB databázy, manuálne vyberaný a kontrolovaný. Najväčšia "feature" tejto databázy je asi objem (tiež ručne zozbieraných) údajov o väzobnej [afinite] [aff].

> Väzobná afinita (binding affinity) je niečo úplne iné ako samotná účinnosť ligandu ("ligand efficacy")... afinita však obecne vyjadruje niečo ako mieru intermolekulárnych síl, teda urýchľuje reakcie a v našom prípade hovorí o lepšom "zapadnutí" ligandu. 

Čo je v databáze:

 * interakcie s malými biologicky aktívnymi molekulami
 * len manuálne pridané data z krystalografických článkov

Druhy väzieb

 * Protein - ligand
 * Protein - cofactor
 * Protein - ligand - cofactor

V databáze sa dá vyhľadávať online, nie ale je možné po sieti pristupovať do databázy priamo. Dostupné je však RESTful-ish rozhranie pre sťahovanie dát v csv/zip. Pre dané PDB poskytuje možnosť stiahnuť si buď upravený PDB file proteínu (odstránenými atómami viac ako 10 Angstrom o proteínu), zoznam podobných proteínov (viď vpravo) alebo zoznam všetkých proteínov danej triedy ( podľa [EC number](https://en.wikipedia.org/wiki/Enzyme_Commission_number)) v databáze.

Príklad zoznamu:

Napr. v zozname napravo máme EC triedu *3.4.21.7*, ktorá obsahuje jednu rodinu proteínov s reprezentatnom 1CEB (PDB) a jedným ďalším proteínom 1CEA. Po názve proteínu vždy nasledujú prvky vstupujúce do reakcie (s popisokom valid/invalid). Jednotlivé stĺpce sú presne popísané na stránkach (MOAD FAQ)[http://www.bindingmoad.org/Home/faq] pod "What is the CSV format?".

```
3.4.21.7,,,,,,,,,
,Family. Representative Entry is ,1CEB,,,,,,,
,,,AMH:A:90,valid,Ki,~,1,uM,C1CC(CCC1CN)C(=O)O,
,,,AMH:B:90,valid,Ki,~,1,uM,C1CC(CCC1CN)C(=O)O,
,,1CEA,,,,,,,
,,,ACA:A:90,valid,Kd,~,11,uM,C(CCC(=O)O)CCN,
,,,ACA:B:90,valid,Kd,~,11,uM,C(CCC(=O)O)CCN,
```

> Z [hlavného článku o MOAD] [D001a]: "Homologous protein families in each EC class are created using the comparison matrix generated from step 1 *pozn. (BLAST)*. At this stage, two entries (A and B in a class) are grouped together into a homologous family if one of the sequences in A is ≥ 90% identical to one of the sequences in B."



[WWW >] [D001a]

[aff]: https://en.wikipedia.org/wiki/Ligand_(biochemistry)#Receptor.2Fligand_binding_affinity
[0001]: http://www.bindingmoad.org/
[D001a]: http://onlinelibrary.wiley.com/doi/10.1002/prot.20512/full
