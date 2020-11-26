//
//  MTLConnectionHandler.h
//  MinewSensorKit
//
//  Created by Minewtech on 2019/8/6.
//  Copyright © 2019 Minewtech. All rights reserved.
//

#import <Foundation/Foundation.h>
#import "MTLDeviceInfo.h"

NS_ASSUME_NONNULL_BEGIN

static NSString *const sServiceString = @"Service";
static NSString *const sReceiveString = @"Receive";
static NSString *const sWriteString = @"Write";
static NSString *const sReadString = @"Read";

typedef NS_ENUM(NSUInteger, MTLConnection) {
    Disconnected = 0,
    Connected,
    Connecting,
    Validating,
    Vaildated,
    VaildateFailed,
    PasswordVaildateFailed,
};

typedef NS_ENUM(NSUInteger, OperationType) {
    UnLockWrited = 1,
    ReadDeviceInfoWrited,
};

typedef void(^MTLPasswordBlock)(NSString *password);

@class MTLConnectionHandler,MTLPeripheral,CBPeripheral;

typedef void(^UnlockCompletion)(BOOL isSuccess, NSError *error);

typedef void(^ReadDeviceInfoCompletion)(MTLDeviceInfo *deviceInfo, BOOL isSuccess, NSError *error);

typedef void(^ConnectionChangeCompletion)(MTLConnection connection);

@interface MTLConnectionHandler : NSObject


// macString of device
@property (nonatomic, strong) NSString *macString;

/**
 current connection status.
 */
@property (nonatomic, readonly, assign) MTLConnection connection;

/**
 Send data to the device
 
 @param operationType type the sending data.
 */
- (void)writeData:(OperationType)operationType;

/**
 Received data from device.
 !!! this is a callback method, please listen to the block, it will execute when receiving data from device.
 @param completionHandler the receiving completion block.
 */
- (void)didUnlock:(UnlockCompletion)completionHandler;

/**
 Read deviceInfo from device.
 !!! this is a callback method, please listen to the block, it will execute when read deviceInfo from device.
 @param completionHandler the receiving completion block.
 */
- (void)didReadDeviceInfo:(ReadDeviceInfoCompletion)completionHandler;

/**
 listen the changes of connection.
 !!! this is a callback method, please listen to the block, it will execute when the device changes connection.
 @param completionHandler the connection changing block.
 */
- (void)didChangeConnection:(ConnectionChangeCompletion)completionHandler;

@end

NS_ASSUME_NONNULL_END
