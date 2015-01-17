  0:     LD  4,0(0)		Set GP
  3:     ST  0,0(0)		Clear dMem[0]
  4:     ST  5,0(6)		Save FP
  5:    LDA  6,-1(6)		
  7:    LDA  0,1(7)		Get PC for Halt
  9:   HALT  0,0,0		Halt
 10:     ST  0,-1(5)		Input Function, store return addr
 11:     IN  0,0,0		     Get input
 12:     LD  7,-1(5)		     Return (end of function)
 13:     ST  0,-1(5)		Output Function, store return addr
 14:     LD  0,-2(5)		     Get output
 15:    OUT  0,0,0		     Give output
 16:     LD  7,-1(5)		     Return (end of function)
 17:     ST  0,-1(5)		Function: store return address in dMem[FP-1]
 18:    LDA  1,-3(5)		  variable: AC1 = address of variable
 19:     LD  0,0(1)		  variable: then AC0 = value of variable
 20:     ST  0,0(6)		
 21:    LDA  6,-1(6)		
 22:    LDC  0,0(0)		
 23:    LDA  6,1(6)		
 24:     LD  1,0(6)		
 25:    SUB  0,1,0		
 27:    LDC  0,0(0)		
 28:    LDC  1,0(0)		
 30:    LDC  0,1(0)		
 26:    JEQ  0,3(7)	30	
 29:    JEQ  1,1(7)	31	
 32:    LDA  1,-2(5)		  variable: AC1 = address of variable
 33:     LD  0,0(1)		  variable: then AC0 = value of variable
 34:     LD  7,-1(5)		Returning (end of function)
 35:    LDC  0,0(0)		  if: Put a 0 in ac0 so we jump over the else part
 37:     ST  5,0(6)		     Function call, save old FP
 38:    LDA  6,-1(6)		
 39:    LDA  6,-1(6)		     Save space for return addr
 40:    LDA  1,-3(5)		  variable: AC1 = address of variable
 41:     LD  0,0(1)		  variable: then AC0 = value of variable
 42:     ST  0,0(6)		
 43:    LDA  6,-1(6)		
 44:    LDA  1,-2(5)		  variable: AC1 = address of variable
 45:     LD  0,0(1)		  variable: then AC0 = value of variable
 46:     ST  0,0(6)		
 47:    LDA  6,-1(6)		
 48:    LDA  1,-2(5)		  variable: AC1 = address of variable
 49:     LD  0,0(1)		  variable: then AC0 = value of variable
 50:     ST  0,0(6)		
 51:    LDA  6,-1(6)		
 52:    LDA  1,-3(5)		  variable: AC1 = address of variable
 53:     LD  0,0(1)		  variable: then AC0 = value of variable
 54:    LDA  6,1(6)		
 55:     LD  1,0(6)		
 56:    DIV  0,1,0		
 57:     ST  0,0(6)		
 58:    LDA  6,-1(6)		
 59:    LDA  1,-3(5)		  variable: AC1 = address of variable
 60:     LD  0,0(1)		  variable: then AC0 = value of variable
 61:    LDA  6,1(6)		
 62:     LD  1,0(6)		
 63:    MUL  0,1,0		
 64:    LDA  6,1(6)		
 65:     LD  1,0(6)		
 66:    SUB  0,1,0		
 67:     ST  0,0(6)		
 68:    LDA  6,-1(6)		
 69:    LDA  5,4(6)		     Set FP to top of frame
 70:    LDA  6,0(6)		     Set SP after locals
 71:    LDA  0,1(7)		     Get return addr
 72:    LDA  7,-56(7)	17	     Jump to function
 73:    LDA  6,0(5)		     Restore old SP
 74:     LD  5,0(5)		     Restore old FP
 75:     LD  7,-1(5)		Returning (end of function)
 31:    JEQ  0,5(7)	37	  if: Jump to else part if test is false (exp == 0)
 36:    JEQ  0,39(7)	76	  if: Jump to the end
 76:     LD  7,-1(5)		End of function (set PC = return addr)
 77:     ST  0,-1(5)		Function: store return address in dMem[FP-1]
 78:     ST  5,0(6)		     Function call, save old FP
 79:    LDA  6,-1(6)		
 80:    LDA  6,-1(6)		     Save space for return addr
 81:    LDA  5,2(6)		     Set FP to top of frame
 82:    LDA  6,0(6)		     Set SP after locals
 83:    LDA  0,1(7)		     Get return addr
 84:    LDA  7,-75(7)	10	     Jump to function
 85:    LDA  6,0(5)		     Restore old SP
 86:     LD  5,0(5)		     Restore old FP
 87:     ST  0,0(6)		  assignment: save value
 88:    LDA  6,-1(6)		
 89:    LDA  1,-2(5)		  variable: AC1 = address of variable
 90:    LDA  6,1(6)		  assignment: retrieve value
 91:     LD  0,0(6)		
 92:     ST  0,0(1)		  assignment: variable = dMem[ac1] = value
 93:     ST  5,0(6)		     Function call, save old FP
 94:    LDA  6,-1(6)		
 95:    LDA  6,-1(6)		     Save space for return addr
 96:    LDA  5,2(6)		     Set FP to top of frame
 97:    LDA  6,0(6)		     Set SP after locals
 98:    LDA  0,1(7)		     Get return addr
 99:    LDA  7,-90(7)	10	     Jump to function
100:    LDA  6,0(5)		     Restore old SP
101:     LD  5,0(5)		     Restore old FP
102:     ST  0,0(6)		  assignment: save value
103:    LDA  6,-1(6)		
104:    LDA  1,-3(5)		  variable: AC1 = address of variable
105:    LDA  6,1(6)		  assignment: retrieve value
106:     LD  0,0(6)		
107:     ST  0,0(1)		  assignment: variable = dMem[ac1] = value
108:     ST  5,0(6)		     Function call, save old FP
109:    LDA  6,-1(6)		
110:    LDA  6,-1(6)		     Save space for return addr
111:     ST  5,0(6)		     Function call, save old FP
112:    LDA  6,-1(6)		
113:    LDA  6,-1(6)		     Save space for return addr
114:    LDA  1,-2(5)		  variable: AC1 = address of variable
115:     LD  0,0(1)		  variable: then AC0 = value of variable
116:     ST  0,0(6)		
117:    LDA  6,-1(6)		
118:    LDA  1,-3(5)		  variable: AC1 = address of variable
119:     LD  0,0(1)		  variable: then AC0 = value of variable
120:     ST  0,0(6)		
121:    LDA  6,-1(6)		
122:    LDA  5,4(6)		     Set FP to top of frame
123:    LDA  6,0(6)		     Set SP after locals
124:    LDA  0,1(7)		     Get return addr
125:    LDA  7,-109(7)	17	     Jump to function
126:    LDA  6,0(5)		     Restore old SP
127:     LD  5,0(5)		     Restore old FP
128:     ST  0,0(6)		
129:    LDA  6,-1(6)		
130:    LDA  5,3(6)		     Set FP to top of frame
131:    LDA  6,0(6)		     Set SP after locals
132:    LDA  0,1(7)		     Get return addr
133:    LDA  7,-121(7)	13	     Jump to function
134:    LDA  6,0(5)		     Restore old SP
135:     LD  5,0(5)		     Restore old FP
136:     LD  7,-1(5)		End of function (set PC = return addr)
  1:    LDA  5,0(4)		Set FP below globals
  2:    LDA  6,0(4)		Set SP below globals
  8:    LDA  7,68(7)	77	Jump to main
  6:    LDA  6,-3(6)		Set SP below locals
