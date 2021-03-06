//
//  SPRectangle.h
//  Sparrow
//
//  Created by Daniel Sperl on 21.03.09.
//  Copyright 2011-2015 Gamua. All rights reserved.
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the Simplified BSD License.
//

#import <Sparrow/SparrowBase.h>
#import <Sparrow/SPPoolObject.h>

NS_ASSUME_NONNULL_BEGIN

@class SPPoint;
@class SPMatrix;

/// Provides constant values for the SPRectangle 'fitInto:' method.
typedef NS_ENUM(NSInteger, SPScaleMode)
{
    /// Specifies that the rectangle is not scaled, but simply centered within the
    /// specified area. */
    SPScaleModeNone,
    
    /// Specifies that the rectangle fills the specified area without distortion but possibly
    /// with some cropping, while maintaining the original aspect ratio. */
    SPScaleModeNoBorder,
    
    /// Specifies that the entire rectangle will be scaled to fit into the specified area,
    /// while maintaining the original aspect ratio. This might leave empty bars at either the
    /// top and bottom, or left and right.
    SPScaleModeShowAll
};

/// The SPRectangle class describes a rectangle by its top-left corner point (x, y) and by 
/// its width and height.

@interface SPRectangle : SPPoolObject <NSCopying>
{
  @protected
    float _x;
    float _y;
    float _width;
    float _height;
}

/// --------------------
/// @name Initialization
/// --------------------

/// Initializes a rectangle with the specified components. _Designated Initializer_.
- (instancetype)initWithX:(float)x y:(float)y width:(float)width height:(float)height;

/// Factory method.
+ (instancetype)rectangleWithX:(float)x y:(float)y width:(float)width height:(float)height;

/// Factory method.
+ (instancetype)rectangle;

/// Factory method.
+ (instancetype)rectangleWithCGRect:(CGRect)rect;

/// -------------
/// @name Methods
/// -------------

/// Determines if a point is within the rectangle.
- (BOOL)containsX:(float)x y:(float)y;

/// Determines if a point is within the rectangle.
- (BOOL)containsPoint:(SPPoint *)point;

/// Determines if another rectangle is within the rectangle.
- (BOOL)containsRectangle:(nullable SPRectangle *)rectangle;

/// Determines if another rectangle contains or intersects the rectangle.
- (BOOL)intersectsRectangle:(nullable SPRectangle *)rectangle;

/// If the specified rectangle intersects with the rectangle, returns the area of intersection.
- (SPRectangle *)intersectionWithRectangle:(nullable SPRectangle *)rectangle;

/// Adds two rectangles together to create a new Rectangle object (by filling in the space between 
/// the two rectangles).
- (SPRectangle *)uniteWithRectangle:(nullable SPRectangle *)rectangle;

/// Calculates the bounds of a rectangle after transforming it by a matrix.
- (SPRectangle *)boundsAfterTransformation:(SPMatrix *)matrix;

/// Increases the size of the specified rectangle by the specified amounts. The center point of the
/// rectangle stays the same, and its size increases to the left and right by the dx value, and to
/// the top and the bottom by the dy value.
- (void)inflateXBy:(float)dx yBy:(float)dy;

/// Calculates a rectangle with the same aspect ratio as the current rectangle, centered
/// within 'into'.
///
/// This method is useful for calculating the optimal viewPort for a certain display size. You can
/// use different scale modes to specify how the result should be calculated; furthermore, you can
/// avoid pixel alignment errors by only allowing whole-number multipliers/divisors
/// (e.g. 3, 2, 1, 1/2, 1/3).
- (SPRectangle *)fitInto:(SPRectangle *)into scaleMode:(SPScaleMode)scaleMode
            pixelPerfect:(BOOL)pixelPerfect;

/// Scales the rectangle by a scale factor (includes x and y coordinates).
- (void)scaleBy:(float)scale;

/// Scales the width and height compontents of the rectangle by a scale factor.
- (void)scaleSizeBy:(float)scale;

/// Sets the members of the rectangle to the specified values.
- (void)setX:(float)x y:(float)y width:(float)width height:(float)height;

/// Sets width and height components to zero.
- (void)setEmpty;

/// Copies the values from another rectangle into the current rectangle.
- (void)copyFromRectangle:(SPRectangle *)rectangle;

/// Compares two rectangles.
- (BOOL)isEqualToRectangle:(SPRectangle *)other;

/// If the rectangle contains negative values for width or height, all coordinates
/// are adjusted so that the rectangle describes the same region with positive values.
- (void)normalize;

/// Creates a CGRect that is equivalent to this instance.
- (CGRect)convertToCGRect;

/// ----------------
/// @name Properties
/// ----------------

/// The x coordinate of the rectangle.
@property (nonatomic, assign) float x;

/// The y coordinate of the rectangle.
@property (nonatomic, assign) float y;

/// The width of the rectangle.
@property (nonatomic, assign) float width;

/// The height of the rectangle.
@property (nonatomic, assign) float height;

/// The y coordinate of the rectangle.
@property (nonatomic, assign) float top;

/// The sum of the y and height properties.
@property (nonatomic, assign) float bottom;

/// The x coordinate of the rectangle.
@property (nonatomic, assign) float left;

/// The sum of the x and width properties.
@property (nonatomic, assign) float right;

/// The location of the top-left corner, determined by the x and y coordinates of the point.
@property (nonatomic, copy) SPPoint *topLeft;

/// The location of the bottom-right corner, determined by the values of the right and bottom properties.
@property (nonatomic, copy) SPPoint *bottomRight;

/// The size of the Rectangle object, determined by the values of the width and height properties.
@property (nonatomic, copy) SPPoint *size;

/// Determines if a rectangle has an empty area.
@property (nonatomic, readonly) BOOL isEmpty;

@end

NS_ASSUME_NONNULL_END
