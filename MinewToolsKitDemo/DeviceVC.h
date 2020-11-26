//
//  DeviceVC.h
//  MinewToolsKitDemo
//
//  Created by minew on 2020/10/15.
//

#import <UIKit/UIKit.h>
#import <MinewToolsKit/MTLCentralManager.h>
#import <MinewToolsKit/MTLPeripheral.h>

NS_ASSUME_NONNULL_BEGIN

@interface DeviceVC : UIViewController

@property (nonatomic, strong) MTLCentralManager *manager;

@property (nonatomic, strong) MTLPeripheral *peripheral;


@end

NS_ASSUME_NONNULL_END
