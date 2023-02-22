define("ace/mode/motorola68000_highlight_rules", ["require", "exports", "module", "ace/lib/oop", "ace/mode/text_highlight_rules"], function(s, e, t) {
    "use strict";

    function d() {
        this.$rules =
            {
                start:
                    [
                        {
                            token: 'keyword.control.assembly',
                            regex: '\\b(?:ABCD|ADD|ADDA|ADDI|ADDQ|ADDX|AND|ANDI|ASL|ASR|BCHG|BCLR|BRA|BSET|BSR|BTST|CHK|CLR|CMP|CMPI|CMPM|DIVS|DIVU|EOR|EORI|EXG|EXT|ILLEGAL|JMP|JSR|LEA|LINK|LSL|LSR|MOVE|MOVEA|MOVEM|MOVEP|MOVEQ|MOVEUSP|MULS|MULU|NBCD|NEG|NEGX|NOP|NOT|OR|ORI|PEA|RESET|ROXL|ROXR|RTE|RTM|RTR|RTS|SBCD|STOP|SUB|SUBA|SUBI|SUBQ|SUBX|SWAP|TAS|TRAP|TRAPV|TST|UNLK|BCC|BHS|BHI|BLS|BLO|BNE|BEQ|BVC|BVS|BPL|BMI|BGE|BLT|BGT|BLE|BF|BT|SCC|SHS|SHI|SLS|SLO|SNE|SEQ|SVC|SVS|SPL|SMI|SGE|SLT|SGT|SLE|SF|ST)(.B|.W|.L)?\\b',
                            caseInsensitive: !0
                        },
                        {
                            token: 'variable.parameter.register.assembly',
                            regex: '\\b(A[0-7]|D[0-7]|SP|PC|SR)\\b',
                            caseInsensitive: !0
                        },
                        {
                            token: 'support.function.directive.assembly',
                            regex: '\\b(?:equ|incbin|dc\.[b|w|l]|ds\.[b|w|l]|set|include|org|end)\\b',
                            caseInsensitive: !0
                        },
                        {
                            token: 'support.class',
                            regex: /(#|@)[0-9]+/
                        },
                        {
                            token: 'support.class',
                            regex: /\$[A-F0-9]+/,
                            caseInsensitive: !0
                        },
                        {
                            token: 'string.assembly',
                            regex: /'([^\\']|\\.)*'/
                        },
                        {
                            token: 'string.assembly',
                            regex: /"([^\\"]|\\.)*"/
                        },
                        {
                            token: 'comment.assembly',
                            regex: ';.*$',
                            caseInsensitive: !0
                        },
                        {
                            token: 'variable.other',
                            regex: /^[a-zA-Z][a-zA-Z0-9_]*:?(\s*)$/,
                            caseInsensitive: !0
                        }
                        ,
                        {
                            token: 'variable.other',
                            regex: /[a-zA-Z][a-zA-Z0-9_]*$/,
                            caseInsensitive: !0
                        }
                    ]
            }, this.normalizeRules()
    }
    var p = s("../lib/oop"),
        s = s("./text_highlight_rules").TextHighlightRules;
    d.metaData = {
        fileTypes: ["asm"],
        name: "Motorola 68000",
        scopeName: "source.assembly"
    }, p.inherits(d, s), e.Motorola68000HighlightRules = d
}), define("ace/mode/folding/coffee", ["require", "exports", "module", "ace/lib/oop", "ace/mode/folding/fold_mode", "ace/range"], function(s, e, t) {
    "use strict";
    var d = s("../../lib/oop"),
        p = s("./fold_mode").FoldMode,
        m = s("../../range").Range,
        s = e.FoldMode = function() {};
    d.inherits(s, p),
        function() {
            this.getFoldWidgetRange = function(s, e, t) {
                var d = this.indentationBlock(s, t);
                if (d) return d;
                var p = /\S/,
                    d = (r = s.getLine(t)).search(p);
                if (-1 != d && "#" == r[d]) {
                    for (var n, d = r.length, i = s.getLength(), a = t, o = t; ++t < i;) {
                        var r, c = (r = s.getLine(t)).search(p);
                        if (-1 != c) {
                            if ("#" != r[c]) break;
                            o = t
                        }
                    }
                    return a < o ? (n = s.getLine(o).length, new m(a, d, o, n)) : void 0
                }
            }, this.getFoldWidget = function(s, e, t) {
                var d = s.getLine(t),
                    p = d.search(/\S/),
                    n = s.getLine(t + 1),
                    i = s.getLine(t - 1),
                    a = i.search(/\S/),
                    o = n.search(/\S/);
                if (-1 == p) return s.foldWidgets[t - 1] = -1 != a && a < o ? "start" : "", "";
                if (-1 == a) {
                    if (p == o && "#" == d[p] && "#" == n[p]) return s.foldWidgets[t - 1] = "", s.foldWidgets[t + 1] = "", "start"
                } else if (a == p && "#" == d[p] && "#" == i[p] && -1 == s.getLine(t - 2).search(/\S/)) return s.foldWidgets[t - 1] = "start", s.foldWidgets[t + 1] = "";
                return s.foldWidgets[t - 1] = -1 != a && a < p ? "start" : "", p < o ? "start" : ""
            }
        }.call(s.prototype)
}), define("ace/mode/motorola68000", ["require", "exports", "module", "ace/lib/oop", "ace/mode/text", "ace/mode/assembly_x86_highlight_rules", "ace/mode/folding/coffee"], function(s, e, t) {
    "use strict";

    function d() {
        this.HighlightRules = i, this.foldingRules = new a, this.$behaviour = this.$defaultBehaviour
    }
    var p = s("../lib/oop"),
        n = s("./text").Mode,
        i = s("./motorola68000_highlight_rules").Motorola68000HighlightRules,
        a = s("./folding/coffee").FoldMode;
    p.inherits(d, n),
        function() {
            this.lineCommentStart = [";"], this.$id = "ace/mode/motorola68000"
        }.call(d.prototype), e.Mode = d
}), window.require(["ace/mode/motorola68000"], function(s) {
    "object" == typeof module && "object" == typeof exports && module && (module.exports = s)
});