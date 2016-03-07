Zapisky
=========

Vsetky clanky su cislovane 4 cifernym kodom (0000-9999).
> `0001` Brainstorming consensus methods in practice

Knihy maju prefix B a 3 ciferny kod (B000 - B999) + priradenu skratku
> `B003` Alberts : Essential Cell Biology 4th edition `[Ecb4]`.

Linky budu mat prefix L nasledovany 3 cifernym kodom a dodatocny popisok.

> `L001` [Databaza prirodovedeckych a biomedicinskych clankov Pubmed](http://www.ncbi.nlm.nih.gov/pubmed) `[W: Pubmed]`

### 0001 Brainstorming consensus methods in practice

*Dariusz Plewczynski, U. Warsaw*

 * Moderne consensus scoring metody vyuzivaju kombinaciu viacerych metod ML
 * Kombinuju algoritmy, ktore su len lokalne vyhodne
 * Ensemble metody ako bagging alebo boosting boli uspesne pouzite pre zlepsenie prediktorov na zaklade agregacie viacerych horsich ciastkovych funkcii (nekorelovanych/ slabo korelovanych)

Popisuje pouzitie a moznosti kombinacie metod strojoveho ucenia ako *Support Vector Machines (SVM)*, *Artificial Neural Networks (ANN/NN)*, *Clustering* alebo *K-nearest neighbors (KNN)*.

Novy pristup - Brainstorming - snazi sa kombinovat velmi siroke spektrum algoritmov, pricom pouziva rozne doplnujuce informacie. Netrenuje na jednom datasete - snazi sa najst relacie medzi vysledkami z treningu nad roznorodymi datami.

#### Hlavne myslienky

Our approach is similar to other `ensemble methods`, yet differently from `bagging` (combines
many unstable predictors to produce a ensemble stable predictor), or `boosting` (combines
many weak but stable predictors to produce an ensemble strong predictor), it focuses of the
use of `heterogeneous set of algorithms` in order to capture even remote, weak similarity of
the predicted sample to the training cases.

> "*Ensemble methods*: In statistics and machine learning, ensemble methods use multiple learning algorithms to obtain better predictive performance than could be obtained from any of the constituent learning algorithms."
> --Wikipedia

The `consensus learning protocol`. Input objects are characterized by the set of
descriptors, in most cases by the vectors of real or binary numbers. In the case of proteins
typically amino acids sequence string and/or its 3D structure (positions of all atoms in
Cartesian space) are used for describing proteins. The set of input objects is then passed to a
set of computational tools in order to `enrich the information` used in training by external
sources. In the case of protein sequences its 3D structural models (predicted by structure
prediction web servers), `physical or chemical properties` of each amino acid of the sequence,
set of homological sequences (identified by PSI-BLAST or other methors), `biological annotations` that can be found in external databases and processed by text mining techniques,
and many others. Then the resulting data is stored in SQL database. All training objects, theirdescription and additional annotations are then processed by feature `decomposition module`
in order to evaluate the `statistical significance` of each descriptor or representation, find some
`similarities between objects`, their features, annotations. In that way algorithm `prepare a set of independent training datasets`, in order to probe different representations of training data.
All datasets are then used for training `several different machine learning methods` (SVM,
ANN, RF, DT and many others). Each classifier learn separately in classification phase on
meta set of training data, then results of ensemble of predictors is fused into single consensus
prediction. The `consensus module`, namely MLcons meta-learner, is the core part of
brainstorming approach. Each ML is used independently to predict class membership for a
query object. `The consensus is then build using results from all representations and features describing this object by different learners in prediction phase. The final output includes predicted class membership, statistical model with performances of each learning modules, trained consensus and reliability scores for prediction.`

> "*Boosting*: Boosting is a machine learning ensemble meta-algorithm for primarily reducing bias, and also variance in supervised learning, and a family of machine learning algorithms which convert weak learners to strong ones. A weak learner is defined to be a classifier which is only slightly correlated with the true classification (it can label examples better than random guessing). In contrast, a strong learner is a classifier that is arbitrarily well-correlated with the true classification."
> --Wikipedia

> "*Support Vector Machines*: Given a set of training examples, each marked for belonging to one of two categories, an SVM training algorithm builds a model that assigns new examples into one category or the other, making it a non-probabilistic binary linear classifier. An SVM model is a representation of the examples as points in space, mapped so that the examples of the separate categories are divided by a clear gap that is as wide as possible. New examples are then mapped into that same space and predicted to belong to a category based on which side of the gap they fall on."
> --Wikipedia

[0001 original >] [0001]

Stav: precitane, prebrat znovu ked budem vediet viac o ML

### 0002 A Biology Primer for Computer Scientists

*Franco P. Preparata, Brown U.*

 * DNA, RNA, proteiny
 * Centralna dogma molekularnej biologie
 * Zakaldy replikacie DNA, transkripcie do RNA a syntezy proteinov
 * Primarna, sekundarna, terciarna a kvarterna struktura proteinov

[0002 original >] [0002]

Stav: precitane, vycerpane - viac v `B004` Essential Cell Biology


[0001]: http://arxiv.org/pdf/0910.0949
[0002]: https://cs.brown.edu/courses/csci1810/bioprimer.pdf

### MIT 6.034 AI: Lec 9. Visual Object Recognition

#### Signal offset recognition by convolution
Majme z signály dané funkciami $f(x)$ a $g(x)$ (+ nejaký šum). Konvolúciou zvýhodníme riešenia kde sa signály prekrývajú a znevýhodníme tie ktoré sú mimo fázy (a opačné amplitúdy sú penalizované vlasne ešte viac)

`$$\argmax_y \int_x f(x)\cdot g(x-y)dx$$`

Relatívne jednoducho by sme rozšírili pre viac viac dimenzií:

$$\argmax_{x_1, y_1} \int_x\int_y f(x,y) \cdot g(x-x_1, y-y_1) dx dy$$
