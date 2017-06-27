// $Id$


#ifndef _OUTPUTSET_HPP_
#define _OUTPUTSET_HPP_

#include <set>

class OutputSet {


public:
  struct sSetElement {
    int vc_start;
    int vc_end;
    int pri;
    int output_port;
  };

  void Clear( );
  void Add( int output_port, int vc, int pri = 0 );
  void AddRange( int output_port, int vc_start, int vc_end, int pri = 0 );

  bool OutputEmpty( int output_port ) const;
  int NumVCs( int output_port ) const;
  
  const set<sSetElement> & GetSet() const;

  int  GetVC( int output_port,  int vc_index, int *pri = 0 ) const;
  bool GetPortVC( int *out_port, int *out_vc ) const;
private:
  set<sSetElement> _outputs;
};

inline bool operator<(const OutputSet::sSetElement & se1, 
	       const OutputSet::sSetElement & se2) {
  return se1.pri > se2.pri; // higher priorities first!
}

#endif


