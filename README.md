# LACHENAL_Lab3

## Introduction

Ce TP permet d'utiliser toutes les bases de co-design vu précédemment. L'objectif de ce TP est d'utiliser l'accéléromètre de la carte DE10 avec un bus I2C et d'afficher les valeurs sur des afficheurs 7segments. On a besoin d'un boutton poussoir pour changer l'axe sur l'affichage et d'un timer pour afficher les valeurs toutes les secondes.

## Architecture du systeme

L'architecture du système est toujours composé d'un processeur NIOS II, d'un JTAG UART pour faire du debogage à l'aide du terminal, d'une mémoire de 40 Ko, de 6 PIO en sortie de largeur 4 bits pour les afficheurs 7 segments, un PIO de 1 bit en entrée pour le bouton poussoir et d'un timer.

Voici l'architecture : 

![Architecture](Architecture.PNG)

En plus du Qsys, l'afficheur 7 segments à été rajouté en vhdl ce qui permettra de brancher les PIO en entrée sur 4 bits et de sortir sur l'afficheur sur 7 bits et le vhdl du 7 segments précédent a été modifié pour rajouter le -.

## Programme C

Pour calibrer l'accéléromètre, il faut modifier les registres d'offset de l'ADXL345. Avant la première écriture on fait une lecture pour activer l'écriture.

Ensuite le calibrage est effectué en regardant les valeurs résiduels sur chaque axe et on applique une correction sur les offsets.

La partie BCD a été réalisé dans la fonction BCD en gérant la partie négative. Cette fonction permet d'afficher les valeurs sur l'afficheur 7 segments.

Il faut aussi penser à modifier le registre data format pour être en full résolution. Comme l'accéléromètre à une sensibilité réglée sur +/- 2g il faut appliquer un facteur d'échelle de 3.9.

Pour gérer la partie négative, on regarde si le MSB des valeurs dataX, dataY, dataZ sur 16 bits est à 1 puis on fait le complément A2.

![scale_factor](scale_factor.PNG)


## Résultats

Le bouton poussoir permet bien de changer l'affichage des axes sur les afficheurs 7 segments et le BCD marche. L'interruption du timer est effectué toutes les secondes et affiche les valeurs.

## Conclusion

Ce TP m'as permis de gérer plusieurs niveau d'interruptions, avec un timer et un bouton poussoir qui prioritaire sur le timer.

