import React, { useRef, useState, useEffect } from 'react'
import { useLoadedMonitor } from '../Monitor';

const ModelView = props => {
    const { monitor, readyState } = useLoadedMonitor();
    const canvasRef = useRef(null)

    // const draw = ctx => {
    //     ctx.fillStyle = '#000000'
    //     ctx.beginPath()
    //     ctx.arc(50, 100, 20, 0, 2 * Math.PI)
    //     ctx.fill()
    // }

    // useEffect(() => {

    //     const canvas = canvasRef.current
    //     const context = canvas.getContext('2d')

    //     //Our draw come here
    //     draw(context)
    // }, [draw])


    useEffect(() => {
        monitor.modelView.init();
    }, []);

    return <canvas ref={canvasRef} id="modelViewCanvas" {...props} />
}


export default ModelView