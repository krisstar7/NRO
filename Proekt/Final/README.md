# Proektna naloga NRO

> [!IMPORTANT]
> Vsi .cpp datoteke kompiliraj s flag -fopenmp. Ta projekt je o paralelizaciji :exploding_head:

### Glavne datoteke
- main.cpp - Glavni program(Rešuje problem in generira VTK file)
- poročilo.tex - Poročilo za proekt
- gauss.cpp in gauss.m - Gauss-Seidl solvers(preberijo A_b.txt, rešijo problem in print(time_elapsed))(gauss.cpp je modifikacija main.cpp)(gauss.m izvaja kod serijski, ampak ima komentirano linija za paralelizacija)
- exportA_b.cpp - Doloci file A_b.txt(modifikacija main.cpp)
- strongScaling.m - Riše graf strong scaling(izhaja iz plot_strong_scaling.m iz teden11 vaje)
- maxThreads.cpp - Določi maximalne threadov

### Sekundarne datoteke
- primer2mreza.txt - vhodni podatki
- ./Imgs - slike za poročilo
- rez.vtk - Rezultantni vtk file
- A_b.txt - Ni je dodaden, kjer je velik. Lahko generirate s exportA_b.cpp