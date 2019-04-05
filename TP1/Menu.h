
/** \brief              Muestra el menu principal con los datos actualizados de A y B.
 *
 * \param est_x int     El estado actual de A (si fue o no ingresado).
 * \param est_y int     El estado actual de B (si fue o no ingresado).
 * \param x float       Variable A.
 * \param y float       Variable B.
 * \return void         No devuelve nada.
 *
 */
void mostrarMenu(int est_x, int est_y, float x, float y);



/** \brief              Le pide al usuario el ingreso de una opcion (1-5). Dentro se evaluara cada caso.
 *
 * \return void         No devuelve nada.
 *
 */
void elegirOpcion();



/** \brief              Le pide al usuario el ingreso de un numero.
 *
 * \return float        Devuelve el numero ingresado por el usuario.
 *
 */
float ingresarNumero();



/** \brief              Comprueba el estado de las variables A y B.
 *
 * \param est_a int     El estado actual de A (si fue o no ingresado).
 * \param est_b int     El estado actual de B (si fue o no ingresado).
 * \return int          Devuelve el estado de ambas variables (1 si las dos fueron ingresadas, sino 0).
 *
 */
int comprobarEstados(int est_a, int est_b);



/** \brief              Valida si una variable contiene un numero entero o no.
 *
 * \param n float       La variable a validar (A o B).
 * \return int          Devuelve 1 si el numero es entero, sino 0.
 *
 */
int validarEntero(float n);
