var completions = [
    { value: 'ADD',  score: 4, meta: 'Instruction' },
    { value: 'ADDI', score: 4, meta: 'Instruction' },
    { value: 'ADDQ', score: 4, meta: 'Instruction' },
    { value: 'ADDX', score: 4, meta: 'Instruction' },
    { value: 'ADDA', score: 4, meta: 'Instruction' },

    { value: 'SUB',  score: 4, meta: 'Instruction' },
    { value: 'SUBI', score: 4, meta: 'Instruction' },
    { value: 'SUBQ', score: 4, meta: 'Instruction' },
    { value: 'SUBX', score: 4, meta: 'Instruction' },
    { value: 'SUBA', score: 4, meta: 'Instruction' },

    { value: 'AND',  score: 1, meta: 'Instruction' },
    { value: 'ANDI', score: 1, meta: 'Instruction' },

    { value: 'OR',   score: 1, meta: 'Instruction' },
    { value: 'EOR',   score: 1, meta: 'Instruction' },
    { value: 'ORI',  score: 1, meta: 'Instruction' },
    { value: 'EORI',   score: 1, meta: 'Instruction' },

    { value: 'ASL',  score: 2, meta: 'Instruction' },
    { value: 'ASR',  score: 2, meta: 'Instruction' },
    { value: 'LSL',  score: 2, meta: 'Instruction' },
    { value: 'LSR',  score: 2, meta: 'Instruction' },

    { value: 'ROXL',  score: 2, meta: 'Instruction' },
    { value: 'ROXR',  score: 2, meta: 'Instruction' },
    { value: 'ROL',  score:  2, meta: 'Instruction' },
    { value: 'ROR',  score:  2, meta: 'Instruction' },

    { value: 'MULS', score: 4, meta: 'Instruction' },
    { value: 'MULU', score: 4, meta: 'Instruction' },

    { value: 'DIVS', score: 4, meta: 'Instruction' },
    { value: 'DIVU', score: 4, meta: 'Instruction' },

    { value: 'CLR', score: 4, meta: 'Instruction' },

    { value: 'BT',   score: 1, meta: 'Instruction' },
    { value: 'BF',   score: 1, meta: 'Instruction' },
    { value: 'BHI',  score: 3, meta: 'Instruction' },
    { value: 'BLS',  score: 3, meta: 'Instruction' },
    { value: 'BCC',  score: 2, meta: 'Instruction' },
    { value: 'BCS',  score: 2, meta: 'Instruction' },
    { value: 'BNE',  score: 3, meta: 'Instruction' },
    { value: 'BEQ',  score: 3, meta: 'Instruction' },
    { value: 'BVC',  score: 2, meta: 'Instruction' },
    { value: 'BVS',  score: 2, meta: 'Instruction' },
    { value: 'BPL',  score: 2, meta: 'Instruction' },
    { value: 'BMI',  score: 2, meta: 'Instruction' },
    { value: 'BGE',  score: 3, meta: 'Instruction' },
    { value: 'BLT',  score: 3, meta: 'Instruction' },
    { value: 'BGT',  score: 3, meta: 'Instruction' },
    { value: 'BLE',  score: 3, meta: 'Instruction' },

    { value: 'DBT',   score: 1, meta: 'Instruction' },
    { value: 'DBF',   score: 1, meta: 'Instruction' },
    { value: 'DBHI',  score: 2, meta: 'Instruction' },
    { value: 'DBLS',  score: 2, meta: 'Instruction' },
    { value: 'DBCC',  score: 1, meta: 'Instruction' },
    { value: 'DBCS',  score: 1, meta: 'Instruction' },
    { value: 'DBNE',  score: 2, meta: 'Instruction' },
    { value: 'DBEQ',  score: 2, meta: 'Instruction' },
    { value: 'DBVC',  score: 1, meta: 'Instruction' },
    { value: 'DBVS',  score: 1, meta: 'Instruction' },
    { value: 'DBPL',  score: 1, meta: 'Instruction' },
    { value: 'DBMI',  score: 1, meta: 'Instruction' },
    { value: 'DBGE',  score: 2, meta: 'Instruction' },
    { value: 'DBLT',  score: 2, meta: 'Instruction' },
    { value: 'DBGT',  score: 2, meta: 'Instruction' },
    { value: 'DBLE',  score: 2, meta: 'Instruction' },

    { value: 'ST',   score: 1, meta: 'Instruction' },
    { value: 'SF',   score: 1, meta: 'Instruction' },
    { value: 'SHI',  score: 2, meta: 'Instruction' },
    { value: 'SLS',  score: 2, meta: 'Instruction' },
    { value: 'SCC',  score: 1, meta: 'Instruction' },
    { value: 'SCS',  score: 1, meta: 'Instruction' },
    { value: 'SNE',  score: 2, meta: 'Instruction' },
    { value: 'SEQ',  score: 2, meta: 'Instruction' },
    { value: 'SVC',  score: 1, meta: 'Instruction' },
    { value: 'SVS',  score: 1, meta: 'Instruction' },
    { value: 'SPL',  score: 1, meta: 'Instruction' },
    { value: 'SMI',  score: 1, meta: 'Instruction' },
    { value: 'SGE',  score: 2, meta: 'Instruction' },
    { value: 'SLT',  score: 2, meta: 'Instruction' },
    { value: 'SGT',  score: 2, meta: 'Instruction' },
    { value: 'SLE',  score: 2, meta: 'Instruction' },

    { value: 'CMPI',  score: 4, meta: 'Instruction' },
    { value: 'CMP',   score: 4, meta: 'Instruction' },
    { value: 'CMPM',  score: 2, meta: 'Instruction' },
    { value: 'CMPA',  score: 2, meta: 'Instruction' },

    { value: 'BCLR', score: 2, meta: 'Instruction' },
    { value: 'BTST', score: 2, meta: 'Instruction' },
    { value: 'BCHG', score: 2, meta: 'Instruction' },
    { value: 'BSET', score: 2, meta: 'Instruction' },

    { value: 'MOVE', score: 5, meta: 'Instruction' },
    { value: 'MOVEM', score: 1, meta: 'Instruction' },
    { value: 'MOVEP', score: 1, meta: 'Instruction' },
    { value: 'MOVEQ', score: 3, meta: 'Instruction' },
    { value: 'MOVEA', score: 5, meta: 'Instruction' },

    { value: 'NEG',  score: 3, meta: 'Instruction' },
    { value: 'NEGX', score: 2, meta: 'Instruction' },
    { value: 'NOT',  score: 3, meta: 'Instruction' },
    { value: 'NOP',  score: 1, meta: 'Instruction' },

    { value: 'EXT',  score: 2, meta: 'Instruction' },

    { value: 'NBCD', score: 1, meta: 'Instruction' },
    { value: 'ABCD', score: 1, meta: 'Instruction' },
    { value: 'SBCD', score: 1, meta: 'Instruction' },
    { value: 'SWAP', score: 5, meta: 'Instruction' },
    { value: 'ILLEGAL', score: 1, meta: 'Instruction' },
    { value: 'TAS', score: 1, meta: 'Instruction' },
    { value: 'TRAP', score: 5, meta: 'Instruction' },
    { value: 'TRAPV', score: 1, meta: 'Instruction' },
    { value: 'LINK', score: 1, meta: 'Instruction' },
    { value: 'UNLK', score: 1, meta: 'Instruction' },
    { value: 'RESET', score: 1, meta: 'Instruction' },

    { value: 'RTE',  score: 2, meta: 'Instruction' },
    { value: 'RTS',  score: 5, meta: 'Instruction' },
    { value: 'RTR', score: 2, meta: 'Instruction' },
    
    { value: 'JSR',  score: 5, meta: 'Instruction' },
    { value: 'JMP',  score: 5, meta: 'Instruction' },

    { value: 'LEA',  score: 5, meta: 'Instruction' },
    { value: 'PEA',  score: 2, meta: 'Instruction' },

    { value: 'CHK',  score: 1, meta: 'Instruction' },
    { value: 'EXG',  score: 1, meta: 'Instruction' },

    { value: 'BRA',  score: 4, meta: 'Instruction' },
    { value: 'BSR',  score: 5, meta: 'Instruction' },


    { value: 'DC',   score: 4, meta: 'Directive' },
    { value: 'DS',   score: 4, meta: 'Directive' },
    { value: 'EQU',  score: 2, meta: 'Directive' },
    { value: 'SET',  score: 2, meta: 'Directive' },
    { value: 'END',  score: 1, meta: 'Directive' },
    { value: 'ORG',  score: 4, meta: 'Directive' },
    { value: 'INCLUDE',  score: 1, meta: 'Directive' },
    { value: 'INCBIN',  score: 1, meta: 'Directive' },

    { value: 'D0',  score: 3, meta: 'Register' },
    { value: 'D1',  score: 3, meta: 'Register' },
    { value: 'D2',  score: 3, meta: 'Register' },
    { value: 'D3',  score: 3, meta: 'Register' },
    { value: 'D4',  score: 3, meta: 'Register' },
    { value: 'D5',  score: 3, meta: 'Register' },
    { value: 'D6',  score: 3, meta: 'Register' },
    { value: 'D7',  score: 3, meta: 'Register' },
    { value: 'A0',  score: 3, meta: 'Register' },
    { value: 'A1',  score: 3, meta: 'Register' },
    { value: 'A2',  score: 3, meta: 'Register' },
    { value: 'A3',  score: 3, meta: 'Register' },
    { value: 'A4',  score: 3, meta: 'Register' },
    { value: 'A5',  score: 3, meta: 'Register' },
    { value: 'A6',  score: 3, meta: 'Register' },
    { value: 'A7',  score: 3, meta: 'Register' },
    { value: 'SP',  score: 3, meta: 'Register' },
    { value: 'PC',  score: 3, meta: 'Register' },
    { value: 'SR',  score: 3, meta: 'Register' },

    { value: 'B',  score: 6, meta: 'Instruction size' },
    { value: 'W',  score: 6, meta: 'Instruction size' },
    { value: 'L',  score: 6, meta: 'Instruction size' }

]  

var myCompleter = { 
    getCompletions: function(editor, session, pos, prefix, callback) { 
        callback(null, completions); 
    } 
}; 
