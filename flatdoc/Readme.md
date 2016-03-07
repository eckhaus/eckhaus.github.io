Zápisky
=========

Všetky články sú číslované 4-ciferným kódom (0000-9999).
> `0001` Brainstorming consensus methods in practice

Knihy majú prefix B a 3-ciferný kod (B000 - B999) + priradenú skratku
> `B003` Alberts : Essential Cell Biology 4th edition `[Ecb4]`.

Linky budú mať prefix L nasledovaný 3-ciferným kódom a dodatočný popisok.

> `L001` [Datábaza prírodovedeckých a biomedicínskych článkov Pubmed](http://www.ncbi.nlm.nih.gov/pubmed) `[W: Pubmed]`

### 0001 Brainstorming consensus methods in practice

*Dariusz Plewczynski, U. Warsaw*

 * Moderné consensus scoring metódy využívajú kombináciu viacerých metód ML
 * Kombinujú algoritmy, ktoré sú len lokálne výhodne / presné
 * Ensemble metódy ako bagging alebo boosting boli úspešne použité pre zlepšenie prediktorov na základe agregácie viacerých horších čiastkových funkcií (nekorelovaných/ slabo korelovaných)

Popisuje použitie a možnosti kombinácie metód strojového učenia ako *Support Vector Machines (SVM)*, *Artificial Neural Networks (ANN/NN)*, *Clustering* alebo *K-nearest neighbors (KNN)*.

Nový prístup - Brainstorming - snaží sa kombinovať veľmi široké spektrum algoritmov, pričom používa rôzne doplňujúce informácie. Netrénuje na jednom datasete - snaží sa nájsť relácie medzi výsledkami z tréningu nad rôznorodými dátami.

#### Hlavné myšlienky

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

Stav: prečítané, prebrať znovu keď budem vedieť viac o ML

### 0002 A Biology Primer for Computer Scientists

*Franco P. Preparata, Brown U.*

 * DNA, RNA, proteíny
 * Centrálna dogma molekulárnej biológie
 * Zákaldy replikácie DNA, transkripcie do RNA a syntézy proteínov
 * Primárna, sekundárna, terciárna a kvartérna štruktúra proteínov

[0002 original >] [0002]

Stav: prečítané, vyčerpané - viac v `B004` Essential Cell Biology


[0001]: http://arxiv.org/pdf/0910.0949
[0002]: https://cs.brown.edu/courses/csci1810/bioprimer.pdf

## MIT 6.034 AI

### Lec 9. Visual Object Recognition

#### Signal offset recognition by convolution
Majme z signály dané funkciami $f(x)$ a $g(x)$ (+ nejaký šum). Konvolúciou zvýhodníme riešenia kde sa signály prekrývajú a znevýhodníme tie ktoré sú mimo fázy (a opačné amplitúdy sú penalizované vlasne ešte viac)

> Convolutional NN? Co je to zač? Má to niečo spoločné so samotnou konvolúciou? Ako presne fungujú konvolučné filtre v grafike? 

$$\argmax_y \int_x f(x)\cdot g(x-y)dx$$

Jednoducho by sme rozšírili pre viac viac dimenzií:

$$\argmax_{x_1, y_1} \int_x\int_y f(x,y) \cdot g(x-x_1, y-y_1) dx dy$$

Hlavná myšlienka: pri učení nepoužívame príliš malé detaily (tie su málo špecifické a namatchuje sa skoro hocičo), ani príliš komplexné objekty - tie môžu byť zas príliš rozmanité a ťažko detekovateľné. Kombináciou viacerých jednoduchých objektov vieme často dostať jednoducho rozlíšiteľný a zároveň detekovateľný vzor.

> **A:** Asi sa niečo podobné dá využiť v AI - niektoré konvolučné filtre detekujú hrany a pod. Ide len o jednoduché prenásobenie konvolučnej matice ([kernelu](https://en.wikipedia.org/wiki/Kernel_(image_processing)) a rovnako veľkého výseku obrázka prvok po prvku a následné sčítanie.

> *Matica detektoru hrán* ([Sobel](https://en.wikipedia.org/wiki/Sobel_operator)): 
> $\begin{bmatrix}-1 & 0 & 1 // -2 & 0 & 2 // -1 & 0 & 1\end{bmatrix}$

### Lec 10. Introduction to Learning, Nearest Neighbors

Two kinds of learning:

 * regularity ("Buldozer Computing")
  * nearest neighbors (simplest, pattern recognition)
  * neural nets (mimicing biology)
  * boosting (theory)
 * constraints ("Human-like")
  * One shot l.
  * Explanation based l.

Feature detector + Comparator = Library -> Recognition

#### Nearest Neighbors

Example: Electrical cover recognition problem

 * Plot 

