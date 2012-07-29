// Copyright 2012 the SK authors. All rights reserved.

#ifndef TFM_H_
#define TFM_H_

#include "message.h"
#include "slice.h"
#include "tfm_descriptor.h"
#include "value_accessors.h"

namespace sk {

// TFM stands for "Timeline freshness message". TFMs are signed statements
// about the recency of information on a timeline server.
class TFM : public Message {
 public:
  explicit TFM(int version);
  virtual ~TFM();

  static TFM* ParseText(Slice in) {
    return static_cast<TFM*>(Message::ParseText(in));
  }

  static TFM* ParseBinary(Slice* in) {
    return static_cast<TFM*>(Message::ParseBinary(in));
  }

  PROPERTY(, uint64_t, max_published_sn,
           Integer, TFMDescriptor::kMaxPublishedSN, value);
  PROPERTY(, uint32_t, max_published_timestamp,
           Timestamp, TFMDescriptor::kMaxPublishedTimestamp, timestamp);
  PROPERTY(, uint64_t, max_sn,
           Integer, TFMDescriptor::kMaxSN, value);
  PROPERTY(, uint32_t, max_timestamp,
           Timestamp, TFMDescriptor::kMaxTimestamp, timestamp);
  PROPERTY(, const std::string&, signature,
           Blob, TFMDescriptor::kSignature, data);
  PROPERTY(, uint64_t, tid,
           Integer, TFMDescriptor::kTID, value);
  PROPERTY(, uint32_t, timestamp,
           Timestamp, TFMDescriptor::kTimestamp, timestamp);
};

}  // namespace sk

#endif  // TFM_H_
