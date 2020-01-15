#################################################################################
# Un exemple de machine learning simple en utilisant la librairie sklearn.
#
# Le but de ce fichier est juste de donner une idée de comment cette librairie est
# utilisée afin d'aider ceux qui voudraient débuter en datscience mais ne savent pas par où commencer.
#
# Le script présenté içi est fortement inspiré de ce qui a été présenté par Fabien Moutarde
# dans son cours "Apprentissage Artificiel" (S1333/5)
#
# Notez que la librairie sklearn lance beaucoup de warning, mais la plupart peuvent
# simplement être ignorés.
#
# Contributeurs : Le Rezal P18
#################################################################################

inputMessage = "---> Appuyez sur Enter <---"

########################### Etape 1 - Mise en forme des données #################

input(f"\nEtape 1 - Mise en forme des données\n{inputMessage}\n")

# La librairie sklearn comporte plusieurs bases de données classiques pour l'apprentissage
# du machine learning. Ici on charge une base de données de chiffres écrits à la main.
from sklearn.datasets import load_digits
# Le but de notre algorithme de machine learning sera d'associer chaque nombre manuscrit
# à sa valeur.


# On charge la base de données complète.
digits = load_digits()


# On met en forme les données que l'on a reçues afin qu'elles soient plus faciles à traiter.
data = digits.images.reshape((len(digits.images), -1))

# Pour plus de clarté, on va nommer l'ensemble des images manuscrites en entrée x
# et l'ensemble des valeurs correspondantes (les valeur réelles que notre algorithme est censé deviner) y
x = data
y = digits.target

# Notez que toutes ces étapes peuvent être retrouver en regardant la documentation
# de la librairie digits dans sklearn.


############ Etape 2 - Exemple simplifié d'usage de la librairie sklearn ########

input(f"\nEtape 2 - Exemple simplifié d'usage de la librairie sklearn\n{inputMessage}\n")

# La librairie sklearn comporte un grand nombre d'algorithmes préimplémentés de machine learning.
# Pour utiliser ces algorithmes il suffit de les importer. Pour cette exemple on va commencer
# avec mon algorithme favori : les forêts aléatoires.
from sklearn.ensemble import RandomForestClassifier

# La librairie sklearn est très standardisée, et les étapes qui suivent sont les mêmes
# quelque soit l'algorithme choisi (les noms des méthodes sont homogènes sur la librairie)

# Step 1 : On déclare une forêt aléatoire. Ici on a gardé les valeurs par défaut.
rfc = RandomForestClassifier()

# Step 2 : On entraine l'algorithme sur des données d'entrée.
rfc.fit(x,y)

# Step 3 : On admire le résultat.
print(f"\nScore obtenu sur l'échantillon d'entrainement : {rfc.score(x,y)}\n")

# L'usage montré ici ne correspond pas à ce qui est fait dans la réalité, car
# dans la mesure où on a évalué la performance de notre algorithme sur les données
# sur lequelles il a été entrainé, on s'expose à de l'overfitting.

############################# Etape 3 - Train/Test ##############################

input(f"\nEtape 3 - Train/Test\n{inputMessage}\n")

# Afin d'éviter (ou au moins de détecter l'overfitting, on choisi souvent de séparer
# nos données en deux échantillons :
# - un échantillon "Train" sur lequel on va faire apprendre l'algorithme
# - un échantillon "Test" sur lequel on va vailder notre modèle pour voir
#   s'il généralise bien ce qu'il a appris sur l'échantillon de test.

# On import une fonction toute faite qui va séparer aléatoirement nos données en
# un échantillon train et un échantillon test.
from sklearn.model_selection import train_test_split

# On sépare les données en train et test (à chaque fois il nous faut récupérer
# la donnée d'entrée x mais également la valeur visée y).
x_test, x_train, y_test, y_train = train_test_split(x,y)

# On entraine une nouvelle forêt aléatoire sur l'échantillon d'entrainement.
rfc = RandomForestClassifier()
rfc.fit(x_train,y_train)

# On teste l'efficacité de l'estimateur obtenu sur l'échantillon de test.
# La précision obtenue sur l'échantillon de test est en général (beaucoup)
# moins bonne que celle obtenue sur l'échantillon d'entrainement.
print(f"\nScore obtenu sur l'échantillon d'entrainement : {rfc.score(x_train,y_train)}\n")
print(f"\nScore obtenu sur l'échantillon de test : {rfc.score(x_test,y_test)}\n")


########################### Etape 4 - Hyperparamètres ###########################

input(f"\nEtape 4 - Hyperparamètres\n{inputMessage}\n")

# Nous avons obtenu un premier estimateur capable d'associer à un chiffre manuscrit
# sa valeur réelle. Cela étant beaucoup d'algorithmes de machine learning
# ont des "hyperparamètres", c'est à dire des paramètres dont la valeur va modifier
# l'estimateur obtenu à la fin de l'entrainement, mais dont il n'est pas possible
# de déterminer la valeur optimale à partir des données d'entrée.

# tl;dr : les hyperparamètres sont des valeurs qu'il faut donner à sklearn
# lorsque l'on crée un estimateur, et la précision de l'estimateur dépendra
# des hyperparamètres choisis.

# On montre l'influence des hyperparamètres en prenant comme exemple un réseau neuronal.
from sklearn.neural_network import MLPClassifier

# Les hyperparamètres d'un MLPClassifier (Multi-Layer Perceptron Classifier)
# sont décrits dans la documentation de sklearn. Notez que sklearn donne des
# valeurs par défaut à tous ces hyperparamètres, donc vous pouvez ne changer que
# ceux qui vous intéresse, ou même ne passer aucun argument et utiliser les
# valeurs prédefines de la librairie.

# Création d'un réseau neuronal avec un premier jeu d'hyperparamètres.
mlp1 = MLPClassifier(hidden_layer_sizes = (8,8), activation = "relu", solver = "adam")
mlp1.fit(x_train,y_train)

# Création d'un autre réseau de neurones avec un jeu de paramètres différents.
mlp2 = MLPClassifier(hidden_layer_sizes = (16), activation = "tanh", solver = "sgd")
mlp2.fit(x_train,y_train)

# Comparaison des deux estimateurs obtenus.
print(f"\nScore obtenu sur l'échantillon d'entrainement : mlp1 - {mlp1.score(x_train,y_train)} vs mlp2 - {mlp2.score(x_train,y_train)}\n")
print(f"\nScore obtenu sur l'échantillon de test : mlp1 - {mlp1.score(x_test,y_test)} vs mlp2 - {mlp2.score(x_test,y_test)}\n")


########################### Etape 5 - Précision/Rappel ##########################

input(f"\nEtape 5 - Précision/Rappel\n{inputMessage}\n")

# En pratique le score d'un estimateur de machine learning ne suffit pas à dire
# si le choix d'hyperparamètres qui a été fait est le bon, il une information plus
# fine pour pouvoir faire un choix de paramètres vraiment éclairé.

# Pour des classifieurs, on utilise souvent la courbe précision rappel afin de
# juger un estimateur. Je ne vais pas expliquer ici la théorie derrière cette courbe,
# si cela vous intéresse je vous encourage à suivre un cours sur le sujet du machine
# learning ou bien à regarder sur internet. Je ne montre ici que la syntaxe associée.

# Pour tracer la courbe
import matplotlib.pyplot as plt

# On importe la fonction pour faire des courbes Précision/Rappel.
from sklearn.metrics import precision_recall_curve

# On va faire cet exemple sur un adaboost appuyé sur des arbres de décision
from sklearn.tree import DecisionTreeClassifier
from sklearn.ensemble import AdaBoostClassifier

# On commence par faire l'apprentissage
dtc = DecisionTreeClassifier(max_depth=4)
# L'algorithme adaboost est un peu particulier, si vous êtes intéressés regardez
# le sur internet pour comprendre.
adb = AdaBoostClassifier(dtc,n_estimators=100)
adb.fit(x_train,y_train)

# On utilise notre estimateur entrainé pour prédire les valeurs associées aux
# chiffres manscrits dans l'échantillon d'entrainement.
probabilityPredictionsADB = adb.predict_proba(x_test)
# probabilityPreditionsADB contient, pour chaque chiffer manuscrit de l'échantillon
# de test, la probabilité qu'il se trouve dans une des classes de sortie.
# Ici nos classes de sortie sont les valeurs possibles des chiffres manuscrits,
# à savoir 0, 1, 2, 3, 4, 5, 6, 7, 8, 9

# Nombre d'éléments de l'échantillon de test.
nombreTests = len(x_test)

# On va utiliser les valeurs prédites pour tracer la courbe Précision/Rappel
# de chacune de nos dix classes.
for classeChiffreManuscrit in range(10):
    # Liste contenant pour chaque élémet de x_test la probabilité de se trouver dans la classe que l'on est en train de regarder.
    listProbabilitésDeClasseChiffreManuscrits = [0 for i in range(nombreTests)]
    # 1 si l'élément se trouve dans la classe courante, 0 sinon.
    listProbabilitésRéelles = [0 for i in range(nombreTests)]
    for elementIndex in range(nombreTests):
        listProbabilitésDeClasseChiffreManuscrits[elementIndex] = probabilityPredictionsADB[elementIndex][classeChiffreManuscrit]
        listProbabilitésRéelles[elementIndex] = y_test[elementIndex] == classeChiffreManuscrit

    # On crée la courbe Précision/Rappel
    precision, recall, threshold = precision_recall_curve(listProbabilitésRéelles, listProbabilitésDeClasseChiffreManuscrits)
    plt.plot(recall,precision,label = f"Classe {classeChiffreManuscrit}")

# Affichage
plt.xlabel("Rappel", fontweight = "bold", fontsize = 18)
plt.ylabel("Precision", fontweight = "bold", fontsize = 18)
plt.title("Courbe précision rappel", fontweight = "bold", fontsize = 20)
plt.legend()
PrecisionRecallCurveFileName = "PrecisionRecallCurveExample.png"
print(f"\nSauvegarde de la courbe précision rappel dans le fichier {PrecisionRecallCurveFileName}\n")
plt.savefig(PrecisionRecallCurveFileName)
# Nécessaire pour éviter que matplotlib ne superpose les différentes figures
plt.clf()

########################### Etape 6 - Cross-Validation ##########################

input(f"\nEtape 6 - Cross-Validation\n{inputMessage}\n")

# Dans la mesure où trouver les parammètres optimaux d'un modèle de machine
# learning est un processus heuristique (i.e. fait à la main) assez long et
# pénible, mais aussi pour s'assure que les données d'entrainement et de validation
# soient utilisées au mieux, on peut automatiser tout ce processu par une cross-validation

# Comme pour les courbes précision rappel, je ne vais pas rentrer dans la théorie
# de la cross-validation ici, mais si cela vous intéresse même conseil, suivez un cours
# d'apprentissage artificiel ou bien regardez sur internet.

# Utilisé pour un simple np.arange à la fin.
import numpy as np

# On importe la fonction utilisée pour faire de la cross validation.
from sklearn.model_selection import GridSearchCV

# On va montrer cette exemple sur un SVC (Support Vector Classifier)
from sklearn.svm import SVC

# On commence par définir les paramètres que l'on veut faire varier et les valeurs
# qu'ils vont prendre.
parameters = {"kernel":("linear","rbf","linear","poly"), "C":[10**(i-3) for i in range(6)]}

# On crée notre estimateur mais on ne l'entraine pas, la cross validation s'en occupera.
svc = SVC()

# On crée notre cross validation pour l'estimateur choisi.
clf = GridSearchCV(estimator=svc, param_grid=parameters)

# On initialize la cross validation de notre estimateur. Notez que la cross validation
# va s'occuper elle même de séparer les échantillon entre train et test, donc
# il faut lui donner toutes les données disponibles pour l'entrainement.
clf.fit(x,y)

# Notez que la Cross-Validation est une méthode de brute-force, par suite faites
# attention à ne pas faire varier trop de paramètres à la fois sur des algorithmes
# gourmands en calculs, faute de quoi la Cross-Validation risque de prendre
# un temps considérable.

# On récupère le score de l'estimateur pour chaque jeu de paramètres possible.
# Il faut également les remettre en forme pour faciliter l'affichage plus tard.
scores = clf.cv_results_["mean_test_score"].reshape(len(parameters["kernel"]), len(parameters["C"]))

# On crée le graphe du score des différents jeux de paramètres.
plt.imshow(scores, interpolation = "none")
plt.colorbar()
plt.title("Score de Cross Validation", fontweight = "bold", fontsize = 20)
plt.xlabel("C", fontweight = "bold", fontsize = 18)
plt.ylabel("Noyau", fontweight = "bold", fontsize = 18)
plt.ylim((-0.5,1.5))
plt.xticks(np.arange(len(parameters["C"])), parameters["C"], fontsize = 15)
plt.yticks(np.arange(len(parameters["kernel"])), parameters["kernel"], rotation = 90, fontsize = 15)
plt.tight_layout()

# On affiche le résultat

CrossValidationFileName = "CrossValidationExample.png"
print(f"\nSauvegarde de la cross validation dans le fichier {CrossValidationFileName}\n")
plt.savefig(CrossValidationFileName)
