CREATE TABLE moteurs(
   idMoteur INT,
   cylindree INT,
   nombreCylindres INT,
   puissance INT,
   typeCarburant VARCHAR(20),
   PRIMARY KEY(idMoteur)
);

CREATE TABLE versions(
   idVersion INT,
   nomVersion VARCHAR(50),
   nomModele VARCHAR(50),
   nomMarque VARCHAR(50),
   PRIMARY KEY(idVersion)
);

CREATE TABLE versions_moteurs(
   idMoteur INT,
   idVersion INT,
   PRIMARY KEY(idMoteur, idVersion),
   FOREIGN KEY(idMoteur) REFERENCES moteurs(idMoteur),
   FOREIGN KEY(idVersion) REFERENCES versions(idVersion)
);
