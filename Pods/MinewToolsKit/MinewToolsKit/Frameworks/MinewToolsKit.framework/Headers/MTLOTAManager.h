//
//  MTLOTAManager.h
//  shoppingCar
//
//  Created by minew on 2020/5/7.
//  Copyright © 2020 minew. All rights reserved.
//

#import <Foundation/Foundation.h>

NS_ASSUME_NONNULL_BEGIN

// ota progress change block
typedef void(^OTAProgressBlock)(float);

@class MTLConnectionHandler;

@interface MTLOTAManager : NSObject

typedef void(^CompletionHandler)(BOOL isSuccess, NSError *error);

+ (void)startOTAUpdate:(MTLConnectionHandler *)connectionHandler OTAData:(NSData *)otaData progressHandler:(OTAProgressBlock)progressHandler completionHandler:(CompletionHandler)completionHandler;


@end

NS_ASSUME_NONNULL_END
