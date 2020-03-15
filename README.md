PAV - P2: detección de actividad vocal (VAD)
============================================

Esta práctica se distribuye a través del repositorio GitHub [Práctica 2](https://github.com/albino-pav/P2),
y una parte de su gestión se realizará mediante esta web de trabajo colaborativo.  Al contrario que Git,
GitHub se gestiona completamente desde un entorno gráfico bastante intuitivo. Además, está razonablemente
documentado, tanto internamente, mediante sus [Guías de GitHub](https://guides.github.com/), como
externamente, mediante infinidad de tutoriales, guías y vídeos disponibles gratuitamente en internet.


Inicialización del repositorio de la práctica.
----------------------------------------------

Para cargar los ficheros en su ordenador personal debe seguir los pasos siguientes:

*	Abra una cuenta GitHub para gestionar esta y el resto de prácticas del curso.
*	Cree un repositorio GitHub con el contenido inicial de la práctica (sólo debe hacerlo uno de los
	integrantes del grupo de laboratorio, cuya página GitHub actuará de repositorio central):
	-	Acceda la página de la [Práctica 3](https://github.com/albino-pav/P2).
	-	En la parte superior derecha encontrará el botón **`Fork`**. Apriételo y, después de unos segundos,
		se creará en su cuenta GitHub un proyecto con el mismo nombre (**P2**). Si ya tuviera uno con ese 
		nombre, se utilizará el nombre **P2-1**, y así sucesivamente.
*	Habilite al resto de miembros del grupo como *colaboradores* del proyecto; de este modo, podrán
	subir sus modificaciones al repositorio central:
	-	En la página principal del repositorio, en la pestaña **:gear:`Settings`**, escoja la opción 
		**Collaborators** y añada a su compañero de prácticas.
	-	Éste recibirá un email solicitándole confirmación. Una vez confirmado, tanto él como el
		propietario podrán gestionar el repositorio, por ejemplo: crear ramas en él o subir las
		modificaciones de su directorio local de trabajo al repositorio GitHub.
*	En la página principal del repositorio, localice el botón **Branch: master** y úselo para crear
	una rama nueva con los primeros apellidos de los integrantes del equipo de prácticas separados por
	guion (**fulano-mengano**).
*	Todos los miembros del grupo deben realizar su copia local en su ordenador personal.
	-	Copie la dirección de su copia del repositorio apretando en el botón **Clone or download**.
		Asegúrese de usar *Clone with HTTPS*.
	-	Abra una sesión de Bash en su ordenador personal y vaya al directorio **PAV**. Desde ahí, ejecute:

		```.sh
		git clone dirección-del-fork-de-la-práctica
		```

	-	Vaya al directorio de la práctica `cd P2`.
	-	Cambie a la rama **fulano-mengano** con la orden:

		```.sh
		git checkout fulano-mengano
		```

*	A partir de este momento, todos los miembros del grupo de prácticas pueden trabajar en su directorio
	local del modo habitual.
	-	También puede utilizar el repositorio remoto como repositorio central para el trabajo colaborativo
		de los distintos miembros del grupo de prácticas; o puede serle útil usarlo como copia de seguridad.
	-	Cada vez que quiera subir sus cambios locales al repositorio GitHub deberá confirmar los
		cambios en su directorio local:

		```.sh
		git add .
		git commit -m "Mensaje del commit"
		```

		y, a continuación, subirlos con la orden:

		```.sh
		git push -u origin fulano-mengano
		```

*	Al final de la práctica, la rama **fulano-mengano** del repositorio GitHub servirá para remitir la
	práctica para su evaluación utilizando el mecanismo *pull request*.
	-	Vaya a la página principal de la copia del repositorio y asegúrese de estar en la rama
		**fulano-mengano**.
	-	Pulse en el botón **New pull request**, y siga las instrucciones de GitHub.


Entrega de la práctica.
-----------------------

Responda, en este mismo documento (README.md), los ejercicios indicados a continuación. Este documento es
un fichero de texto escrito con un formato denominado _**markdown**_. La principal característica de este
formato es que, manteniendo la legibilidad cuando se visualiza con herramientas en modo texto (`more`,
`less`, editores varios, ...), permite amplias posibilidades de visualización con formato en una amplia
gama de aplicaciones; muy notablemente, **GitHub**, **Doxygen** y **Facebook** (ciertamente, :eyes:).

En GitHub. cuando existe un fichero denominado README.md en el directorio raíz de un repositorio, se
interpreta y muestra al entrar en el repositorio.

Debe redactar las respuestas a los ejercicios usando Markdown. Puede encontrar información acerca de su
sintáxis en la página web [Sintaxis de Markdown](https://daringfireball.net/projects/markdown/syntax).
También puede consultar el documento adjunto [MARKDOWN.md](MARKDOWN.md), en el que se enumeran los elementos
más relevantes para completar la redacción de esta práctica.

Recuerde realizar el *pull request* una vez completada la práctica.

Ejercicios
----------

### Etiquetado manual de los segmentos de voz y silencio

- Etiquete manualmente los segmentos de voz y silencio del fichero grabado al efecto. Inserte, a 
  continuación, una captura de `wavesurfer` en la que se vea con claridad la señal temporal, el contorno de
  potencia y la tasa de cruces por cero, junto con el etiquetado manual de los segmentos.

![Imagen del Wavesurfer](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/wavesurfer.png)

- A la vista de la gráfica, indique qué valores considera adecuados para las magnitudes siguientes:

	* Incremento del nivel potencia en dB, respecto al nivel correspondiente al silencio inicial, para estar
      seguros de que un segmento de señal se corresponde con voz.

	* Duración mínima razonable de los segmentos de voz y silencio.
	> Observando el problema que podia surgir de decidir una pausa breve o un ruido lejano como silencio o voz hemos decidido incluir dos estados más, tal y como se nos indicaba en la práctica (Maybe_SILENCE o Maybe_VOICE). Se puede observar en el codigo que hemos decidido que como mucho se podría estar 50ms en un estado de duda, ya que creemos que si pasas más de 50 ms en este estado la conclusion que se podria obtener de cambiar de estado sería errónea, por lo que si pasan estos 50 ms el estado volverá a cambiar al estado anterior suponiendo que se trata de un segmento de pausa breve en el habla o de ruido en silencio.

	* ¿Es capaz de sacar alguna conclusión a partir de la evolución de la tasa de cruces por cero?
> Si observamos las gráficas anteriores, se observa que la que más variación contiene es la de la potencia. Se observa principalmente que al inicio de la grabación el nivel de potencia se encuentra muy bajo. Una vez se establece empieza lo que podríamos considerar silencio, que se encuentra ciertos dB por encima de este nivel esmentado. Por otro lado se observa que siempre que hay voz el nivel de potencia se encuentra muy por encima al nivel de silencio, con lo que creemos oportuno que si esta 5dB por encima del nivel del silencio se podrá considerar ya que habrá voz en ese instante.

> A partir del txt que generamos de la práctica anterior, hemos obtenido el ZCR del silencio inicia del .wav, basándonos en estos, no hemos podido destacar muchas condiciones, ya que no se visualizan gran cambios a lo largo del audio, y siempre se encuentran alrededor del nivel de silencio, unos fm/4. En nuestro audio no tenemos ninguna fricativa sorda, que nos harían observar un pico mucho mayor en este apartado.

### Desarrollo del detector de actividad vocal

- Complete el código de los ficheros de la práctica para implementar un detector de actividad vocal tan
  exacto como sea posible. Tome como objetivo la maximización de la puntuación-F `TOTAL`.

- Inserte una gráfica en la que se vea con claridad la señal temporal, el etiquetado manual y la detección
  automática conseguida para el fichero grabado al efecto. 
  
  ![Imagen del Wavesurfer](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/labvsotro.PNG)

- Explique, si existen. las discrepancias entre el etiquetado manual y la detección automática.

> En nuestro caso, la exactitud es del 97,1 % . Asi que en nuestro caso, las diferencies son imperceptibles. 

![](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/97.PNG)

- Evalúe los resultados sobre la base de datos `db.v4` con el script `vad_evaluation.pl` e inserte a 
  continuación las tasas de sensibilidad (*recall*) y precisión para el conjunto de la base de datos (sólo
  el resumen).
  
  ![](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/84.PNG)
  
  
  > En caso de todos los audios el máximo que obtenemos justo corresponde con los mismos valores con los que hemos obtenido nuestro 97,1% y se obtiene un 84,456%. Si observamos un poco todos los ficheros de audio que hemos intentado detectar se observa que un gran número de ficheros se encuentran entre 85% y el 95%, el problema está en que algunos, pocos, se encuentran cerca del 60% y entonces la media baja mucho. El problema de estos puede ser tal y como se explica en la práctica, que el umbral k0 de donde decimos los otros dos, no sea el más óptimos, donde señales con potencias bajas no se detectan correctamente ya que la diferencia entre segmentos de voz y silencio no son muy elevadas.


### Trabajos de ampliación

#### Cancelación del ruido en los segmentos de silencio

- Si ha desarrollado el algoritmo para la cancelación de los segmentos de silencio, inserte una gráfica en
  la que se vea con claridad la señal antes y después de la cancelación (puede que `wavesurfer` no sea la
  mejor opción para esto, ya que no es capaz de visualizar varias señales al mismo tiempo).

 ![](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/cero.PNG)
> En esta imagen observamos como se genera un fichero de salida si el usuario entra por pantalla que quiere que se guarde la información detectada en uno.
 ![](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/out.jpeg)
> Se puede observar que cuando hay un silencio, el valor de la señal es un cero.  
> Para realizar una última comprobación, hicimos a propósito, un ejemplo con umbrales mal elegidos, entonces, el fichero de audio generado era de muy mala calidad y de difícil entendimiento.
De esta forma, estábamos seguros de que el código hacia lo que queríamos.  


#### Gestión de las opciones del programa usando `docopt_c`

- Si ha usado `docopt_c` para realizar la gestión de las opciones y argumentos del programa `vad`, inserte
  una captura de pantalla en la que se vea el mensaje de ayuda del programa.


### Contribuciones adicionales y/o comentarios acerca de la práctica

- Indique a continuación si ha realizado algún tipo de aportación suplementaria (algoritmos de detección o 
  parámetros alternativos, etc.).
  
   ![](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/elegir.PNG)
  
  > Como ampliación nuestra hemos decidido incluir que el usuario pueda decidir la generación de un umbral automático (poniendo un 0) o que lo entre manualmente (1).

> A parte como se observa, nos hemos asegurado que en el caso de que el usuario se equivoque al teclear, si el número introducido no es ni 0 ni 1, salta un mensaje de error para que se introduzca un número nuevo y así el programa no entra en colapso.

   ![](https://github.com/PauGuardia/P2/blob/Guardia-Linde/src/error.PNG)


- Si lo desea, puede realizar también algún comentario acerca de la realización de la práctica que considere
  de interés de cara a su evaluación.
  
> CONCLUSION FINAL:
> Podemos decir que nuestro archivo de audio lo hemos optimizado al máximo consiguiendo de forma automática un 97,1 %. Lo cual es imperceptible si rellenamos el silencio en forma de ceros en un archivo de audio generado por nuestro código. Por otra parte, en la base de datos, hemos obtenido un 84,4%. En algunos casos, obtenemos un porcentaje mayor del 90% y en otros, un poco inferior del 80%. Aunque la mayoría de casos, los resultados estaban alrededor del 85 %.

### Antes de entregar la práctica

Recuerde comprobar que el repositorio cuenta con los códigos correctos y en condiciones de ser 
correctamente compilados con la orden `meson bin; ninja -C bin`. El programa generado (`bin/vad`) será
el usado, sin más opciones, para realizar la evaluación *ciega* del sistema.
