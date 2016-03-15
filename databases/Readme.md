Databázy
=========

### Zdroje na preskúmanie

* [Binding MOAD](http://www.bindingmoad.org/)
* [LigASite](http://www.ligasite.org/)
* [Catalytic Site Atlas (CSA)](http://www.ebi.ac.uk/thornton-srv/databases/CSA/)
* [PDBe PISA, PDBe Fold, PDBe](http://www.ebi.ac.uk/pdbe/node/1)
* [Uniprot (Swissprot+spol.)](http://www.uniprot.org/)
* [Interpro](https://www.ebi.ac.uk/interpro/)
* [Enzyme portal](http://www.ebi.ac.uk/enzymeportal/)
* [Merops](https://merops.sanger.ac.uk/index.shtml)
* [ebi.ac.uk](www.ebi.ac.uk)
* [BioMart: Martservice](http://www.biomart.org/martservice.html)
* [PDBsite](http://wwwmgs.bionet.nsc.ru/mgs/gnw/pdbsite/)
* [BindingDB](https://www.bindingdb.org/bind/index.jsp)
* [RCSB PDB](http://www.rcsb.org/pdb/home/home.do)
* [Expasy](http://www.expasy.org/)
* [EBI Intact](http://www.ebi.ac.uk/intact/)
* [String DB](http://string-db.org/)

### Dátové formáty

* Protein Data Bank format (PDB)
* Simplified molecular-input line-entry system (SMILES)
* mmCIF

### D001 Binding MOAD

*Michigan University, 2004*

Jedna z najväčších databáz svojho druhu. Obsahuje údaje o protein-ligand(-cofactor) interakciách s malými biologicky aktívnymi molekulami (t.j. nie protein-protein interakcie). Ide o výcuc z PDB databázy, manuálne vyberaný a kontrolovaný. Najzaujimavejšia vlastnosť tejto databázy je asi objem (tiež ručne zozbieraných) údajov o väzobnej [afinite] [D001c].

> Väzobná afinita (binding affinity) je niečo úplne iné ako samotná účinnosť ligandu ("ligand efficacy")... afinita však obecne vyjadruje niečo ako mieru intermolekulárnych síl, teda urýchľuje reakcie a v našom prípade hovorí o lepšom "zapadnutí" ligandu. 

**Čo je v databáze:**

 * interakcie s malými biologicky aktívnymi molekulami
 * len manuálne pridané data z krystalografických článkov

**Druhy väzieb:**

 * Protein - ligand
 * Protein - cofactor
 * Protein - ligand - cofactor

V databáze sa dá vyhľadávať online, nie ale je možné po sieti pristupovať do databázy priamo. Dostupné je však RESTful-ish rozhranie pre sťahovanie dát v csv/zip. Pre dané PDB poskytuje možnosť stiahnuť si buď upravený PDB file proteínu (odstránenými atómami viac ako 10 Angstrom o proteínu), zoznam podobných proteínov (viď vpravo) alebo zoznam všetkých proteínov danej triedy ( podľa [EC number](https://en.wikipedia.org/wiki/Enzyme_Commission_number)) v databáze.

> **Ligand may be:**

> * peptide of 10 amino acids or less
> * oligonucleotide of 4 nucleotides or less
> * small organic molecule (e.g. ibuprofen)
> * cofactor (e.g. NADPH)

Príklad zoznamu:

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


 Webové rozhranie (pre PDB=10GS, EC=2.5.1.18):
`www.bindingmoad.org/Pdbrecords/download/CSV/10gs.csv`
`www.bindingmoad.org/Pdbrecords/download/CSV/family385.csv`
`www.bindingmoad.org/Pdbrecords/download/CSV/class_2.5.1.18.csv`

> Z [hlavného článku o MOAD] [D001a]: "Homologous protein families in each EC class are created using the comparison matrix generated from step 1 *pozn. (BLAST)*. At this stage, two entries (A and B in a class) are grouped together into a homologous family if one of the sequences in A is ≥ 90% identical to one of the sequences in B."


[1) L Hu, ML Benson, RD Smith, MG Lerner, HA Carlson. Binding MOAD (Mother Of All Databases).Proteins 2005, 60, 333-40.] [D001a]

[2) A. Ahmed, RD Smith, JJ Clark, JB Dunbar, HA Carlson. Recent improvements to Binding MOAD: a resource for proteinligand binding affinities and structures. Nucl. Acids Res. 2014, 43, D465-D469.] [D001b]

[WWW >] [D0001]


[D0001]: http://www.bindingmoad.org/
[D001a]: http://onlinelibrary.wiley.com/doi/10.1002/prot.20512/full
[D001b]: http://nar.oxfordjournals.org/content/43/D1/D465.fullhttp://nar.oxfordjournals.org/content/43/D1/D465.full
[D001c]: https://en.wikipedia.org/wiki/Ligand_(biochemistry)#Receptor.2Fligand_binding_affinity

###

