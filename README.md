Hecho por: 
- Alejandra sanches
- Juan Bueno
- John Jimenez
----------------------------------------------------------------------------------------------------------------------------------

# Sistema-de-seguridad-con-Arduino

Esto es una propuesta de sistema de suguridad, el cual puede activarse o desactivar mendiande una contraseña. En este sistema tambien cuenta con una barrera laser, alarma e interfaz.
------------------------------------------------------------------------------------------------------------------------------------------
Objetivo:
alertar de un intruzo o equivocacion de contraseña
------------------------------------------------------------------------------------------------------------------------------------------

Para esta propuesta se hizo dos versiones.
- La primera version del sistema no funciono por cuestiones de logica, estructuracion de codigo y conexiones
- Se hizo una reestructuracion de todo el codigo, añadiendo tambien la comunicacion con la interfaz.
  
------------------------------------------------------------------------------------------------------------------------------------------

funciones:
- Cuando el LDR no recibe luz del laser, se dispara inmediatamente una alrma.
- Cuando se digita una contraseña incorrecta, se dispara la alarma y en el display se muestra el mensaje "REPIT PLS" ofreciendo la posibilidad de volver a digitar la contraseña.
- Al digitar la contrasña correcta, la barrera laser se desactiva y no se activa ninguna alarma. La barrera puede volver a activarse digitando una una contraseña incorrcta o desde la interfaz.
- En el display en la fila 0 se muestra el mensaje "WELCOME!" , en la fila 1 "Pass:"
- al lado del mensaje de la fila 1 del display, lo que se digita se muestra como asterisco "*"
- Es necesario conectar interfaz con el sistema, ya que en este caso se comunican por el mismo puerto serial. Tambien es necesario dar clic en el boton "Close" y que la accion de ese boton desconecta la interfaz del sistema y cierra la ventana de la interfaz.

Desde la interfaz se puede:
- Cambiar la contraseña
- Activar la barrera laser
- Armar y Desarmar la alarma
- encender y apagar el display
