# Tic Tac Toe AI 
<p>In order to compile simply type <b>make</b> this will create an executable named <b>ttt</b>.</p>

## Runtime Commands 
<p> There are a series of commands you can utilize during execution to properly play the game. </p>
<p><b>Commands:</b></p>      

* "show" (no arguments)
  * <p><u> Show the current board</u></p>    

* "reset" (no arguments)
  * <p><u> Restart the game to a clean board</u></p>     

* "move" (piece[X,O] row[A,B,C] column[1,2,3])
  * <p><u> Move a piece to a specified location, for example moving 'X' to 3rd row 1st column, "move X C 3".</u></p>     

* "choose" (piece[X,O])    
  * <p>Allow the AI to pick the best position for a piece, for example choosing where to put the next 'O', "choose O".</p>

* "pruning" optional (toggle[on,off])
  * <p>Without any arguments this command simply shows if Alpha-Beta Pruning is enabled for the search tree<p>
  * <p>Specifying an argument toggles Alpha-Beta Pruning to either on or off, for example to turn pruning off, "pruning off".</p>

* "quit" (no arguments)
  * <p>Exits the program</p>
