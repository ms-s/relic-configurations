Some notes on compiling ECDSA for Arduino Mega 2560 using the configurations files on https://github.com/ms88/relic-configurations/
- This short tutorial assumes that you know how to compile and upload Arduino programmes from Eclipse. (Read http://playground.arduino.cc/Code/Eclipse) It also assumes that you know how to compile a library using CMake. 
- You could use compiled versions of the library based on relic version 0.3.1 directly from https://github.com/ms88/relic-configurations/. Just download fast-librelic_s.a or lowmem-librelic_s.a depending on your requirements and import it into your own Eclipse project. No need of compiling. They work on Arduino Mega 2560. You need to import the static library in the same way you import static libraries for Arduino as described in http://playground.arduino.cc/Code/Eclipse under the section "Setup your project". (Look at Select AVR C/C++ Linker -> Libraries. It explains how you configure the linker to use static libraries.) Remember that you will have 2 different static libraries: one for Arduino (libcore.a) and one for relic (librelic.a).
- If you are importing relic to a C++ programme (most Arduino programmes are C++), import with extern as:

	extern "C" {
			#include < relic.h >
		}

- You would also require relavent header files imported in your project. (Look at headers-fast-relic and headers-lowmem-relic).
- Incase you feel the need of compiling your own version, use a modified CMakeLists.txt. This is available in the git repository. Before using it, replace ***** in the file with the actual paths as they exist on your system. These changes were necessary to include the Arduino header files and also set the AVR compiler and linker paths and flags. 
- Also, if you are using assembly instructions (-DARITH=avr-asm-163), you will need to change the files that exist in /relic-0.3.1/src/low/avr-asm-163. For all the files with .s extension, change the ".arch atmega128" to ".arch atmega2560". 
- This tutorial is for linux users. If you have problems compiling on other systems, please do not contact me. If you cannot run Arduino code from Eclipse, please do not contact me.
- Incase you are interested in other libraries or are interested in comparing performance with exisitng results of ECDSA, please refer the following:
	- http://tools.ietf.org/html/draft-aks-crypto-sensors-02
	- http://kth.diva-portal.org/smash/record.jsf?searchId=2&pid=diva2:563280
	- http://ieeexplore.ieee.org/xpl/articleDetails.jsp?tp=&arnumber=6424089
	- http://lib.tkk.fi/Dipl/2012/urn100663.pdf

- Just read the file relic_cp_ecdsa.c in the library.
	You will find that there are 3 functions that are quite intuitive from the name themselves:


		void cp_ecdsa_gen(bn_t d, ec_t q)  : Generate a key pair
		void cp_ecdsa_sign(bn_t r, bn_t s, unsigned char *msg, int len, bn_t d) : Sign something
		int cp_ecdsa_ver(bn_t r, bn_t s, unsigned char *msg, int len, ec_t q) : verify something

- If you look at the test file, it gives you an idea on how to use them. See the file (test_cp.c):


		static int ecdsa(void) 
		{
		    int code = STS_ERR;
		    bn_t d, r;
		    ec_t q;
		    unsigned char msg[5] = { 0, 1, 2, 3, 4 };

		    bn_null(d);
		    bn_null(r);
		    ec_null(q);

		    TRY {
			bn_new(d);
			bn_new(r);
			ec_new(q);

			TEST_BEGIN("ecdsa is correct") {
			    cp_ecdsa_gen(d, q);
			    cp_ecdsa_sign(r, d, msg, 5, d);
			    TEST_ASSERT(cp_ecdsa_ver(r, d, msg, 5, q) == 1, end);
			} TEST_END;
		    } CATCH_ANY {
			ERROR(end);
		    }
		    code = STS_OK;

		  end:
		    bn_free(d);
		    bn_free(r);
		    ec_free(q);
		    return code;
		} 

- If you are using assembly math library (both fast-relic, lowmem-relic use assmebly math), i.e. the cmake command contains -DARITH=avr-asm-163 Serial.println will not work directly for debug messages. You would have to print debug messages according to the following pseudocode:
	
		extern "C" {

		#include <relic.h>
		}

		#define PRINT(STRING) \
		   util_copy_rom(str, PSTR(STRING)); \
		   Serial.println(str); \

		void setup(){
		Serial.begin(115200);
		char str[100];
		PRINT("Start");
		//Similarly other Serial.println should be replaced with PRINTs
		//Only static strings are printed using PRINTs, other variables are printed using Serial.println as usual
		}

- Finally, do not forget to cite appropriately. Plagiarism can come to haunt you several years after you are done with what you are doing. 
- Also don't forget to thank and cite the original authors of the library. Without them, this would not have been possible. 


-- Configuring RELIC 0.3.1...

-- Available switches (default = CHECK, VERBS, DOCUM):

		   DEBUG=[off|on] Build with debugging support.
		   PROFL=[off|on] Build with profiling support.
		   CHECK=[off|on] Build with error-checking support.
		   VERBS=[off|on] Build with detailed error messages.
		   TRACE=[off|on] Build with tracing support.
		   MULTI=[off|on] Build with multithreading.
		   DOCUM=[off|on] Build documentation.
		   STRIP=[off|on] Build only selected algorithms.
		   QUIET=[off|on] Build with printing disabled.
		   COLOR=[off|on] Build with colored output.
		   BIGED=[off|on] Build with big-endian support.
		   SHLIB=[off|on] Build shared library.
		   STLIB=[off|on] Build static library.
		   STBIN=[off|on] Build static binaries.

-- Number of times each test or benchmark is ran (default = 50, 1000):

		   TESTS=n        If n > 0, build automated tests and run them n times.
		   BENCH=n        If n > 0, build automated benchmarks and run them n * n times.

-- Number of available processor cores (default = 1):

		   CORES=n        If n > 1, build with multithreading support.

-- Available architectures (default = X86_64):

		   ARCH=AVR       Atmel AVR ATMega128 8-bit architecture.
		   ARCH=MSP       TI MSP430 16-bit architecture.
		   ARCH=ARM       ARM 32-bit architecture.
		   ARCH=X86       Intel x86-compatible 32-bit architecture.
		   ARCH=X86_64    AMD x86_64-compatible 64-bit architecture.

-- Available word sizes (default = 64):

		   WORD=8         Build a 8-bit library.
		   WORD=16        Build a 16-bit library.
		   WORD=32        Build a 32-bit library.
		   WORD=64        Build a 64-bit library.

-- Byte boundary to align digit vectors (default = 1):


		   ALIGN=1        Do not align digit vectors.
		   ALIGN=2        Align digit vectors into 16-bit boundaries.
		   ALIGN=8        Align digit vectors into 64-bit boundaries.
		   ALIGN=16       Align digit vectors into 128-bit boundaries.

-- Available modules (default = ALL)

		   WITH=BN       Multiple precision arithmetic.
		   WITH=DV       Temporary double-precision digit vectors.
		   WITH=FP       Prime field arithmetic.
		   WITH=FB       Binary field arithmetic.
		   WITH=EP       Elliptic curves over prime fields.
		   WITH=EB       Elliptic curves over binary fields.
		   WTTH=EC       Elliptic curve cryptography.
		   WITH=HB       Hyperelliptic curve cryptography.
		   WITH=PB       Pairings over binary elliptic curves.
		   WITH=PP       Pairings over prime elliptic curves.
		   WTTH=PC       Pairing-based cryptography.
		   WITH=MD       Message digests (Hash functions).
		   WITH=CP       Cryptographic protocols.
		   WITH=ALL      All of the above.
		   Note: the programmer is responsible for not using unselected modules.

-- Available arithmetic backends (default = easy):

		   ARITH=easy     Easy-to-understand implementation.
		   ARITH=gmp      GNU Multiple Precision library.

-- Available memory-allocation policies (default = AUTO):

		   ALLOC=AUTO     All memory is automatically allocated.
		   ALLOC=STATIC   All memory is allocated statically once.
		   ALLOC=DYNAMIC  All memory is allocated dynamically on demand.
		   ALLOC=STACK    All memory is allocated from the stack.

-- Available pseudo-random number generators (default = FIPS):

	  	 RAND=FIPS      Use the FIPS 186-2 SHA1-based generator. (recommended)

-- Available random number generator seeders (default = DEV):

		   SEED=ZERO      Use a zero seed. (not crypto safe!)
		   SEED=LIBC      Use the libc rand()/random() functions. (not crypto safe!)
		   SEED=DEV       Use /dev/random. (recommended)
		   SEED=UDEV      Use /dev/urandom.
		   SEED=WCGR      Use Windows' CryptGenRandom. (recommended)

-- Supported operating systems (default = LINUX):

		   OPSYS=NONE     Undefined/No operating system.
		   OPSYS=LINUX    GNU/Linux operating system.
		   OPSYS=FREEBSD  FreeBSD operating system.
		   OPSYS=MACOSX   Mac OS X.
		   OPSYS=WINDOWS  Windows operating system.

-- Supported timers (default = HIGH):

		   TIMER=NONE     No timer.
		   TIMER=HREAL    GNU/Linux realtime high-resolution timer.
		   TIMER=HPROC    GNU/Linux per-process high-resolution timer.
		   TIMER=HTHRD    GNU/Linux per-thread high-resolution timer.
		   TIMER=ANSI     ANSI-compatible timer.
		   TIMER=POSIX    POSIX-compatible timer.
		   TIMER=CYCLE    Cycle-counting timer. (architecture-dependant)

-- Multiple precision arithmetic configuration (BN module):

   ** Options for the multiple precision module (default = 1024,DOUBLE,0):

		      BN_PRECI=n        The base precision in bits. Let w be n in words.
		      BN_MAGNI=DOUBLE   A multiple precision integer can store 2w words.
		      BN_MAGNI=CARRY    A multiple precision integer can store w+1 words.
		      BN_MAGNI=SINGLE   A multiple precision integer can store w words.
		      BN_KARAT=n        The number of Karatsuba steps.

   ** Available multiple precision arithmetic methods (default = COMBA;COMBA;MONTY;SLIDE;STEIN;BASIC):

	      BN_METHD=BASIC    Schoolbook multiplication.
	      BN_METHD=COMBA    Comba multiplication.
	      BN_METHD=KnMUL    Karatsuba for (n > 0) steps and MUL multiplication.

	      BN_METHD=BASIC    Schoolbook squaring.
	      BN_METHD=COMBA    Comba squaring.
	      BN_METHD=KnSQR    Karatsuba for (n > 0) steps and SQR squaring.

	      BN_METHD=BASIC    Division-based modular reduction.
	      BN_METHD=BARRT    Barrett modular reduction.
	      BN_METHD=MONTY    Montgomery modular reduction.
	      BN_METHD=RADIX    Diminished radix modular reduction.

	      BN_METHD=BASIC    Binary modular exponentiation.
	      BN_METHD=MONTY    Constant-time Montgomery powering ladder.
	      BN_METHD=SLIDE    Sliding window modular exponentiation.

	      BN_METHD=BASIC    Euclid's standard GCD algorithm.
	      BN_METHD=LEHME    Lehmer's fast GCD algorithm.
	      BN_METHD=STEIN    Stein's binary GCD algorithm.

	      BN_METHD=BASIC    Basic prime generation.
	      BN_METHD=SAFEP    Safe prime generation.
	      BN_METHD=STRON    Strong prime generation.

	      Note: these methods must be given in order. Ex: BN_METHD="K1BASIC;COMBA;BARRT;CONST;SAFEP"

-- Prime field arithmetic configuration (FP module):

   ** Arithmetic precision of the prime field module (default = 256,0,off,off):

	      FP_PRIME=n        The prime modulus size in bits.

	      FP_KARAT=n        The number of Karatsuba levels.
	      FP_PMERS=[off|on] Prefer Pseudo-Mersenne primes over random primes.
	      FP_QNRES=[off|on] Use -1 as quadratic non-residue (make sure that p = 3 mod 8).
	      FP_WIDTH=w        Width w in [2,6] of window processing for exponentiation methods.

   ** Available prime field arithmetic methods (default = BASIC;COMBA;COMBA;MONTY;MONTY;SLIDE):

	      FP_METHD=BASIC    Schoolbook addition.
	      FP_METHD=INTEG    Integrated modular addition.

	      FP_METHD=BASIC    Schoolbook multiplication.
	      FP_METHD=INTEG    Integrated modular multiplication.
	      FP_METHD=COMBA    Comba multiplication.

	      FP_METHD=BASIC    Schoolbook squaring.
	      FP_METHD=INTEG    Integrated modular squaring.
	      FP_METHD=COMBA    Comba squaring.

	      FP_METHD=BASIC    Division-based reduction.
	      FP_METHD=QUICK    Fast reduction modulo special form prime (2^t - c, c > 0).
	      FP_METHD=MONTY    Montgomery modular reduction.

	      FB_METHD=BASIC    Inversion by Fermat's Little Theorem.
	      FB_METHD=BINAR    Binary Inversion algorithm.
	      FB_METHD=MONTY    Mntgomery inversion.
	      FB_METHD=EXGCD    Inversion by the Extended Euclidean algorithm.
	      FB_METHD=LOWER    Pass inversion to the lower level.

	      FP_METHD=BASIC    Binary exponentiation.
	      FP_METHD=SLIDE    Sliding window exponentiation.
	      FP_METHD=MONTY    Constant-time Montgomery powering ladder.

	      Note: these methods must be given in order. Ex: FP_METHD="BASIC;BASIC;COMBA;MONTY;MONTY;SLIDE"

-- Binary field arithmetic configuration (FB module):

   ** Options for the binary elliptic curve module (default = 283,0,on,on,on):

		      FB_POLYN=n        The irreducible polynomial size in bits.
		      FB_KARAT=n        The number of Karatsuba levels.
		      FB_TRINO=[off|on] Prefer trinomials.
		      FB_SQRTF=[off|on] Prefer square-root friendly polynomials.
		      FB_PRECO=[off|on] Precompute multiplication table for sqrt(z).

		      FB_WIDTH=w        Width w in [2,6] of window processing for exponentiation methods.

   ** Available binary field arithmetic methods (default = LODAH;TABLE;QUICK;BASIC;QUICK;QUICK;EXGCD;SLIDE;QUICK):

		      FB_METHD=BASIC    Right-to-left shift-and-add multiplication.
		      FB_METHD=INTEG    Integrated modular multiplication.
		      FB_METHD=RCOMB    Right-to-left comb multiplication.
		      FB_METHD=LCOMB    Left-to-right comb multiplication.
		      FB_METHD=LODAH    L�pez-Dahab comb multiplication with window of width 4.

		      FB_METHD=BASIC    Bit manipulation squaring.
		      FB_METHD=INTEG    Integrated modular squaring.
		      FB_METHD=TABLE    Table-based squaring.

		      FB_METHD=BASIC    Shift-and-add modular reduction.
		      FB_METHD=QUICK    Fast reduction modulo a trinomial or pentanomial.

		      FB_METHD=BASIC    Square root by repeated squaring.
		      FB_METHD=QUICK    Fast square root extraction.

		      FB_METHD=BASIC    Trace computation by repeated squaring.
		      FB_METHD=QUICK    Fast trace computation.

		      FB_METHD=BASIC    Solve a quadratic equation by half-trace computation.
		      FB_METHD=QUICK    Fast solving with precomputed half-traces.

		      FB_METHD=BASIC    Inversion by Fermat's Little Theorem.
		      FB_METHD=BINAR    Binary Inversion algorithm.
		      FB_METHD=ALMOS    Inversion by the Amost inverse algorithm.
		      FB_METHD=EXGCD    Inversion by the Extended Euclidean algorithm.
		      FB_METHD=ITOHT    Inversion by Itoh-Tsuji.
		      FB_METHD=LOWER    Pass inversion to the lower level.

		      FB_METHD=BASIC    Binary exponentiation.
		      FB_METHD=SLIDE    Sliding window exponentiation.
		      FB_METHD=MONTY    Constant-time Montgomery powering ladder.

		      FB_METHD=BASIC    Iterated squaring/square-root by consecutive squaring/square-root.
		      FB_METHD=QUICK    Iterated squaring/square-root by table-based method.

		      Note: these methods must be given in order. Ex: FB_METHD="INTEG;INTEG;QUICK;QUICK;QUICK;QUICK;ALMOS;BASIC;BASIC"

-- Ternary field arithmetic configuration (FT module):

   ** Options for the binary elliptic curve module (default = 509,0,on):

		      FT_POLYN=n        The irreducible polynomial size in trits.
		      FT_KARAT=n        The number of Karatsuba levels.
		      FT_TRINO=[off|on] Prefer trinomials.

   ** Available ternary field arithmetic methods (default = LODAH;TABLE;QUICK;BASIC;EXGCD):

		      FT_METHD=BASIC    Right-to-left shift-and-add multiplication.
		      FT_METHD=INTEG    Integrated modular multiplication.
		      FT_METHD=LODAH    L�pez-Dahab comb multiplication with window of width 4.

		      FT_METHD=BASIC    Bit manipulation cubing.
		      FT_METHD=INTEG    Integrated modular cubing.
		      FT_METHD=TABLE    Table-based cubing.

		      FT_METHD=BASIC    Shift-and-add modular reduction.
		      FT_METHD=QUICK    Fast reduction modulo a trinomial or pentanomial.

		      FT_METHD=BASIC    Cube root by repeated cubing.
		      FT_METHD=QUICK    Fast cube root extraction.

		      FT_METHD=BASIC    Inversion by Fermat's Little Theorem.
		      FT_METHD=BINAR    Binary Inversion algorithm.
		      FT_METHD=EXGCD    Inversion by the Extended Euclidean algorithm.
		      FT_METHD=ALMOS    Inversion by the Amost inverse algorithm.

		      Note: these methods must be given in order. Ex: FT_METHD="INTEG;INTEG;QUICK;QUICK;ALMOS"

-- Prime elliptic curve arithmetic configuration (EP module):

   ** Options for the binary elliptic curve module (default = all on):

		      EP_ORDIN=[off|on] Support for ordinary curves.
		      EP_SUPER=[off|on] Support for supersingular curves.
		      EP_KBLTZ=[off|on] Special support for Koblitz curves.
		      EP_MIXED=[off|on] Use mixed coordinates.

		      EP_PRECO=[off|on] Build precomputation table for generator.
		      EP_DEPTH=w        Width w in [2,6] of precomputation table for fixed point methods.
		      EP_WIDTH=w        Width w in [2,6] of window processing for unknown point methods.

   ** Available binary elliptic curve methods (default = PROJC;LWNAF;COMBS;INTER):

		      EP_METHD=BASIC    Affine coordinates.
		      EP_METHD=PROJC    Jacobian projective coordinates.

		      EP_METHD=BASIC    Binary method.
		      EP_METHD=LWNAF    Left-to-right window NAF method (GLV for Koblitz curves).

		      EP_METHD=BASIC    Binary method for fixed point multiplication.
		      EP_METHD=YAOWI    Yao's windowing method for fixed point multiplication
		      EP_METHD=NAFWI    NAF windowing method for fixed point multiplication.
		      EP_METHD=COMBS    Single-table Comb method for fixed point multiplication.
		      EP_METHD=COMBD    Double-table Comb method for fixed point multiplication.
		      EP_METHD=LWNAF    Left-to-right window NAF method (GLV for Koblitz curves).

		      EP_METHD=BASIC    Multiplication-and-addition simultaneous multiplication.
		      EP_METHD=TRICK    Shamir's trick for simultaneous multiplication.
		      EP_METHD=INTER    Interleaving of window NAFs (GLV for Koblitz curves).
		      EP_METHD=JOINT    Joint sparse form.

		      Note: these methods must be given in order. Ex: EB_METHD="BASIC;LWNAF;COMBD;TRICK"

-- Binary elliptic curve arithmetic configuration (EB module):

   ** Options for the binary elliptic curve module (default = on, w = 4):

		      EB_ORDIN=[off|on] Support for ordinary curves.
		      EB_SUPER=[off|on] Support for supersingular curves.
		      EB_KBLTZ=[off|on] Special support for Koblitz curves.
		      EB_MIXED=[off|on] Use mixed coordinates.
		      EB_PRECO=[off|on] Build precomputation table for generator.
		      EB_DEPTH=w        Width w in [2,6] of precomputation table for fixed point methods.
		      EB_WIDTH=w        Width w in [2,6] of window processing for unknown point methods.

   ** Available binary elliptic curve methods (default = PROJC;LWNAF;COMBS;INTER):

		      EB_METHD=BASIC    Affine coordinates.
		      EB_METHD=PROJC    Projective coordinates (L�pez-Dahab for ordinary curves).

		      EB_METHD=BASIC    Binary method.
		      EB_METHD=LODAH    L�pez-Dahab constant-time point multiplication.
		      EB_METHD=LWNAF    Left-to-right window (T)NAF method.
		      EB_METHD=RWNAF    Right-to-left window (T)NAF method.
		      EB_METHD=HALVE    Halving method.

		      EB_METHD=BASIC    Binary method for fixed point multiplication.
		      EB_METHD=YAOWI    Yao's windowing method for fixed point multiplication
		      EB_METHD=NAFWI    NAF windowing method for fixed point multiplication.
		      EB_METHD=COMBS    Single-table Comb method for fixed point multiplication.
		      EB_METHD=COMBD    Double-table Comb method for fixed point multiplication.
		      EB_METHD=LWNAF    Left-to-right window (T)NAF method.

		      EB_METHD=BASIC    Multiplication-and-addition simultaneous multiplication.
		      EB_METHD=TRICK    Shamir's trick for simultaneous multiplication.
		      EB_METHD=INTER    Interleaving of window (T)NAFs.
		      EB_METHD=JOINT    Joint sparse form.

		      Note: these methods must be given in order. Ex: EB_METHD="BASIC;LWNAF;COMBD;TRICK"

-- Elliptic curve cryptography configuration (EC module):

   ** Options for the binary elliptic curve module (default = on):

		      EC_KBLTZ=[off|on] Prefer Koblitz (prime or binary) curves.

   ** Available elliptic curve methods (default = PRIME):

		      EC_METHD=PRIME    Use prime curves.
		      EC_METHD=CHAR2    Use binary curves.

		      Note: these methods must be given in order. Ex: EC_METHD="BINAR"

-- Binary hyperelliptic genus 2 curve arithmetic configuration (HB module):

   ** Options for the binary elliptic curve module (default = on, w = 4):

		      HB_SUPER=[off|on] Support for supersingular curves.
		      HB_PRECO=[off|on] Build precomputation table for generator.
		      EB_DEPTH=w        Width w in [2,6] of precomputation table for fixed point methods.
		      HB_WIDTH=w        Width w in [2,6] of window processing for unknown point methods.

   ** Available binary elliptic curve methods (default = PROJC;LWNAF;COMBS;INTER):

		      HB_METHD=BASIC    Affine coordinates.
		      HB_METHD=PROJC    Projective coordinates (L�pez-Dahab for ordinary curves).

		      HB_METHD=BASIC    Binary method.
		      HB_METHD=OCTUP    Octupling-based windowing method.

		      HB_METHD=BASIC    Binary method for fixed point multiplication.
		      HB_METHD=YAOWI    Yao's windowing method for fixed point multiplication
		      HB_METHD=NAFWI    NAF windowing method for fixed point multiplication.
		      HB_METHD=COMBS    Single-table Comb method for fixed point multiplication.
		      HB_METHD=COMBD    Double-table Comb method for fixed point multiplication.
		      HB_METHD=LWNAF    Window NAF with width w (TNAF for Koblitz curves).

		      HB_METHD=BASIC    Multiplication-and-addition simultaneous multiplication.
		      HB_METHD=TRICK    Shamir's trick for simultaneous multiplication.
		      HB_METHD=INTER    Interleaving of window NAFs.
		      HB_METHD=JOINT    Joint sparse form.

		      Note: these methods must be given in order. Ex: HB_METHD="BASIC;LWNAF;COMBD;TRICK"

-- Bilinear pairings arithmetic configuration (PP module):

   ** Options for the bilinear pairing module (default = on):

	      PP_PARAL=[off|on] Parallel implementation.

   ** Available bilinear pairing methods (default = BASIC;O-ATE):

	      PP_METHD=BASIC    Basic quadratic extension field arithmetic.
	      PP_METHD=INTEG    Quadratic extension field arithmetic with embedded modular reduction.

	      PP_METHD=BASIC    Basic extension field arithmetic.
	      PP_METHD=LAZYR    Lazy reduced extension field arithmetic.

	      PP_METHD=O_ATE    Optimal ate pairing.

-- Bilinear pairings arithmetic configuration (PB module):

   ** Options for the bilinear pairing module (default = on):

	      PB_PARAL=[off|on] Parallel implementation.

   ** Available bilinear pairing methods (default = ETATS):

	      PB_METHD=ETATS    Eta-t pairing with square roots.
	      PB_METHD=ETATN    Eta-t pairing without square roots.

-- Pairing-based cryptography configuration (PC module):

   ** Available pairing computation methods (default = PRIME):

	      PC_METHD=PRIME    Use prime (asymmetric) setting.
	      PC_METHD=CHAR2    Use binary (symmetric) setting.

-- Message digest configuration (MD module):

   ** Available hash functions (default = SH256):

	      MD_METHD=SHONE    SHA-1 hash function.
	      MD_METHD=SH224    SHA-224 hash function.
	      MD_METHD=SH256    SHA-256 hash function.
	      MD_METHD=SH384    SHA-384 hash function.
	      MD_METHD=SH512    SHA-512 hash function.

-- Cryptographic protocols configuration (CP module):

   ** Options for the cryptographic protocols module (default = PKCS1):

	      CP_RSAPD=BASIC    RSA with basic padding.
	      CP_RSAPD=PKCS1    RSA with PKCS#1 v1.5 padding.
	      CP_RSAPD=PKCS2    RSA with PKCS#1 v2.1 padding.

   ** Available cryptographic protocols methods (default = QUICK;BASIC):

	      CP_METHD=BASIC    Slow RSA decryption/signature.
	      CP_METHD=QUICK    Fast RSA decryption/signature using CRT.

      Note: these methods must be given in order. Ex: CP_METHD="QUICK"

-- Configuring done
-- Generating done
-- Build files have been written to: /home/*****/relic-0.3.1

