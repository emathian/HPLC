library(ggplot2)

########################################################
#               Resultats vecteurs
########################################################

vect=read.table("result_vector_force_forte.txt",head=TRUE)
vect

# SOMME DE DEUX VECTEURS
taille=as.factor(vect$Taille_tab)
p1<- ggplot(vect, aes(x=nb_thread, y=diff1_somme_deux_vect,color=taille)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme de deux vecteurs")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
p1


# SOMME DES ELEMENTS D'UN VECTEUR

p2<- ggplot(vect, aes(x=nb_thread, y=diff2_somme_vect,color=taille)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme des elements d'un vecteur")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
p2


# MULTIPLICATION DE DEUX VECTEURS

p3<- ggplot(vect, aes(x=nb_thread, y=diff3_multi_vect,color=taille)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Multiplication d'un vecteur par un double")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
p3


########################################################
#               Resultats matrices
########################################################

data=read.table("resultats_force_forte_matrix.txt",head=TRUE)
data


# SOMME DE DEUX MATRICES
dimentions=as.factor(data$nb_rows)
g1<- ggplot(data, aes(x=nb_thread, y=diff1_somme_deux_vect,color=dimentions)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme de deux matrices")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
g1



# SOMME DES ELEMENTS D'UNE MATRICE
g2<- ggplot(data, aes(x=nb_thread, y=diff2_somme_vect,color=dimentions)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Somme des elements d'une matrice")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
g2


# MULTIPLICATION DE DEUX MATRICES

g3<- ggplot(data, aes(x=nb_thread, y=diff3_multi_vect,color=dimentions)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Multiplication d'une matrices par un double")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
g3


########################################################
#               Resultats matrices lettre
########################################################

letter=read.table("result_v2_force_forte.txt",head=TRUE)
letter

dimentions=as.factor(letter$nb_rows)
l1<- ggplot(letter, aes(x=nb_thread, y=temps_comptage,color=dimentions)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Denombrement de lettres dans une matrice\nSimple parallelisation")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
l1

l2<- ggplot(letter, aes(x=nb_thread, y=temps_comptage_v2,color=dimentions)) + 
  geom_smooth(method=lm) +
  geom_point() +
  scale_y_continuous(name = "temps d'execution") +
  scale_x_continuous(name = "nombre de threads") +
  ggtitle("Denombrement de lettres dans une matrice \nDouble parallelisation")+
  theme(plot.title = element_text(size = 18, family = "Tahoma", face = "bold"),
        text = element_text(size = 12, family = "Tahoma"),
        axis.title = element_text(face="bold"),
        axis.text.x=element_text(size = 10))
l2
